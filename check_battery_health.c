#include <stdio.h>
#include <stdbool.h>
#include "check_battery_health.h"

int currentLanguage = ENGLISH;

ParameterConfig Config[MAX_PARAMETERS] = {
    {
        "Temperature",
        TEMP_LOWER_LIMIT,
        TEMP_UPPER_LIMIT,
        TEMP_LOWER_LIMIT + (TEMP_UPPER_LIMIT * TOLERANCE_PERCENT),
        TEMP_UPPER_LIMIT - (TEMP_UPPER_LIMIT * TOLERANCE_PERCENT),
        true,
        {
            // English
            { "Low breach", "Warning: Approaching low temperature", "Normal", "Warning: Approaching high temperature", "High breach" },
            // German
            { "Niedriger Verstoß", "Warnung: Annäherung an niedrige Temperatur", "Normal", "Warnung: Annäherung an hohe Temperatur", "Hoher Verstoß" }
        }
    },
    {
        "State of charge",
        SOC_LOWER_LIMIT,
        SOC_UPPER_LIMIT,
        SOC_LOWER_LIMIT + (SOC_UPPER_LIMIT * TOLERANCE_PERCENT),
        SOC_UPPER_LIMIT - (SOC_UPPER_LIMIT * TOLERANCE_PERCENT),
        true,
        {
            // English
            { "Low breach", "Warning: Approaching discharge", "Normal", "Warning: Approaching full charge", "High breach" },
            // German
            { "Niedriger Verstoß", "Warnung: Annäherung an Entladung", "Normal", "Warnung: Annäherung an volle Ladung", "Hoher Verstoß" }
        }
    },
    {
        "Charging rate",
        CR_LOWER_LIMIT,
        CR_UPPER_LIMIT,
        CR_LOWER_LIMIT + (CR_UPPER_LIMIT * TOLERANCE_PERCENT),
        CR_UPPER_LIMIT - (CR_UPPER_LIMIT * TOLERANCE_PERCENT),
        true,
        {
            // English
            { "Low breach", "Warning: Approaching low charge rate", "Normal", "Warning: Approaching high charge rate", "High breach" },
            // German
            { "Niedriger Verstoß", "Warnung: Annäherung an niedrige Ladegeschwindigkeit", "Normal", "Warnung: Annäherung an hohe Ladegeschwindigkeit", "Hoher Verstoß" }
        }
    }
};

// Function to display messages
void dispMessage(char *param, const char *msg) {
    printf("%s: %s\n", param, msg);
}

MsgType determineWarnType(float value, float lowerLimitTol, float upperLimitTol) {
    if (value < lowerLimitTol) return APPROACHING_LOW;
    if (value > upperLimitTol) return APPROACHING_HIGH;
    return IN_RANGE;
}

// Function to check if value is approaching limits
MsgType checkIfValueApproachingLimits(float value, ParameterConfig *param) {
    if (!param->warningEnabled) return IN_RANGE;

    return determineWarnType(value, param->lowerLimitTol, param->upperLimitTol);
}

// Function to check if value is within limits
MsgType checkIfValueWithinLimits(float value, ParameterConfig *param) {  
    if (value < param->lowerLimit) return LOW_BREACH;
    if (value > param->upperLimit) return HIGH_BREACH;
    return checkIfValueApproachingLimits(value, param);
}

// Function to check battery health
int batteryIsOk(float temperature, float soc, float chargeRate) {
	
    int status = 1;
    MsgType msg;
    float paramVal[MAX_PARAMETERS] = {temperature, soc, chargeRate};

    for(int idx=0; idx < MAX_PARAMETERS; idx++) {
        msg = checkIfValueWithinLimits(paramVal[idx], &Config[idx]); 
        dispMessage(Config[idx].name, Config[idx].msgs[currentLanguage][msg]);
        status &= GET_STS_FROM_MSG(msg);
    }

    return status;
}
