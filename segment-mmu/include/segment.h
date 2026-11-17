
#ifndef SEGMENT_H
#define SEGMENT_H

#include <vector>
#include <string>


struct Segment {
    int base;    
    int limit;  
    std::string name; 
};


struct LogicalAddress {
    int segment; 
    int offset;  
};

struct TranslateResult {
    bool ok;            
    int physical;        
    std::string error;  
};


using SegmentTable = std::vector<Segment>;


// Returns an empty table on incomplete input; check std::cin to detect EOF.
SegmentTable loadSegmentTable();

void printSegmentTable(const SegmentTable& table);

TranslateResult translate(const SegmentTable& table, LogicalAddress addr);

#endif
