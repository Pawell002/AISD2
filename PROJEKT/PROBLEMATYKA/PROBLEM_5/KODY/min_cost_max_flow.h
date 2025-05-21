#ifndef MAX_PRZEPLYW_H
#define MAX_PRZEPLYW_H
#include <vector>
#include <utility>
#include "graf_budowa.h"

std::pair<int,int> min_cost_max_flow(std::vector<std::vector<Krawedz>>& graf,int start,int koniec);

#endif
