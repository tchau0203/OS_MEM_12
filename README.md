# HDH_GR12
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


SegmentTable loadSegmentTable();

TranslateResult translate(const SegmentTable& table, LogicalAddress addr);

#endif
