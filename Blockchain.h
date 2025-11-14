#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <string>
#include <vector>
#include <iostream>
#include <ctime>
#include <sstream>
#include <functional>  // ✅ Needed for std::hash

// ---------------- Block Definition ----------------
class Block {
public:
    std::string data;
    std::string prevHash;
    std::string hash;
    time_t timestamp;

    Block(const std::string& d, const std::string& prev) {
        data = d;
        prevHash = prev;
        timestamp = std::time(nullptr);

        // ✅ Proper hash generation using std::hash
        std::hash<std::string> hasher;
        hash = std::to_string(hasher(d + prev + std::to_string(timestamp)));
    }
};

// ---------------- Blockchain Definition ----------------
class Blockchain {
private:
    std::vector<Block> chain;

public:
    Blockchain() {
        chain.push_back(Block("Genesis Block", "0"));
    }

    void addBlock(const std::string& data) {
        std::string prevHash = chain.back().hash;
        chain.push_back(Block(data, prevHash));
    }

    bool verifyChain() const {
        for (size_t i = 1; i < chain.size(); ++i) {
            std::hash<std::string> hasher;
            std::string recalculated = std::to_string(
                hasher(chain[i].data + chain[i - 1].hash + std::to_string(chain[i].timestamp))
            );

            if (recalculated != chain[i].hash)
                return false;
        }
        return true;
    }

    void displayChain() const {
        std::cout << "\n======= Blockchain Ledger =======\n";
        for (const auto& block : chain) {
            std::cout << "Data: " << block.data << "\n"
                      << "PrevHash: " << block.prevHash << "\n"
                      << "Hash: " << block.hash << "\n"
                      << "Time: " << std::ctime(&block.timestamp)
                      << "----------------------------------\n";
        }
    }
};

#endif
