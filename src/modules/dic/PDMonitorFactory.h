#ifndef PD_MONITOR_FACTORY_H_
#define PD_MONITOR_FACTORY_H_

#include <model/MonitorFactory.h>

namespace dic {

class PDMonitorFactory : public MonitorFactory
{
public:
    Monitor *getMonitor(Node const *node, Model *model,
			unsigned int start, unsigned int thin, 
			std::string const &type);
    std::vector<Node const*> defaultNodes(Model *model,
					  std::string const &type) const;
};

}

#endif /* PD_MONITOR_FACTORY_H_ */