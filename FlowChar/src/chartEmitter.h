#ifndef __CHARTEMITTER_H
#define __CHARTEMITTER_H

#include "tree.h"
#include "box.h"

#include <memory>

namespace FC{
namespace BE{

class ChartEmitter
{
private:
    std::shared_ptr<IR::Stm> tree;
    const bool doRedirect;
    std::string chartPath;
    std::unique_ptr<Box> boxes;
    chartT flowchart;
    posT start;

public:
    ChartEmitter(std::shared_ptr<IR::Stm> tree);
    ChartEmitter(std::shared_ptr<IR::Stm> tree, const std::string &chartPath);
    void attachChartInfo();
    void drawFlowChart();
};
    
} // namespace BE
} // namespace FC


#endif
