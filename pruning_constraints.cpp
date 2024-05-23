#include <iostream>
#include <climits>
#include "custom_types/ts.h"
#include "custom_types/state.h"
#include <algorithm>
#include <math.h>



bool check_adversary_pruning_conditions(state& s, const unsigned short m) {
    // no pruning conditions in "wcs_only" version
    return true;
}

