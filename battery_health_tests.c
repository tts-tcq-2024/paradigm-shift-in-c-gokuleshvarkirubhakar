#include <stdio.h>
#include <stdbool.h>
#include <assert.h>
#include "check_battery_health.h"

// Tests
int main() {
    assert(!batteryIsOk(-5.0, 70, 0.7));    	// Low temperature
    assert(batteryIsOk(0, 70, 0.7));		// Boundary temperature - Lower
    assert(batteryIsOk(45, 70, 0.7));    	// Boundary temperature - Upper
    assert(!batteryIsOk(50, 70, 0.7));      	// High temperature
    assert(!batteryIsOk(25, 10, 0.7));      	// Low SOC
    assert(batteryIsOk(25, 20, 0.7));    	// Boundary SOC - Lower
    assert(batteryIsOk(25, 80, 0.7));    	// Boundary SOC - Upper
    assert(!batteryIsOk(25, 90, 0.7));     	// High SOC
    assert(!batteryIsOk(25, 70, -0.1));     	// Low charge rate
    assert(batteryIsOk(25, 70, 0));         	// Boundary CR - Lower
    assert(batteryIsOk(25, 70, 0.8));       	// Boundary CR - Upper
    assert(!batteryIsOk(25, 70, 0.9));      	// High charge rate 
    assert(!batteryIsOk(50, 90, 0.9));      	// All parameters out of range
    assert(batteryIsOk(25, 70, 0.7));       	// Normal parameters
}
