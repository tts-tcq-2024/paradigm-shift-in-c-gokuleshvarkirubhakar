#ifndef CHECK_BATTERY_HEALTH_H_
#define CHECK_BATTERY_HEALTH_H_

#define MAX_MESSAGE_LENGTH   100
// Configureable limits
#define TEMP_UPPER_LIMIT	(45.0f)
#define TEMP_LOWER_LIMIT	(0.0f)
#define SOC_UPPER_LIMIT		(80.0f)
#define SOC_LOWER_LIMIT		(20.0f)
#define CR_UPPER_LIMIT		(0.8f)
#define CR_LOWER_LIMIT		(0.0f)
#define TOLERANCE_PERCENT   (0.05f)

#define GET_STS_FROM_MSG(msg) ((msg) == IN_RANGE || (msg) == APPROACHING_LOW || (msg) ==  APPROACHING_HIGH)

typedef enum{
	ENGLISH,
	GERMAN,
	MAX_LANGUAGES
}LanguageSupport;

typedef enum{
    TEMPERATURE,
    STATE_OF_CHARGE,
    CHARGING_RATE,
    MAX_PARAMETERS
}Parameters;

typedef enum {
    LOW_BREACH,
    APPROACHING_LOW,
    IN_RANGE,
    APPROACHING_HIGH,
    HIGH_BREACH,
    MAX_MSG_TYPES
}MsgType;

typedef struct {
    char *name;
    float lowerLimit;
    float upperLimit;
    float lowerLimitTol;
    float upperLimitTol;
    bool warningEnabled;
    const char msgs[MAX_LANGUAGES][MAX_MSG_TYPES][MAX_MESSAGE_LENGTH];
}ParameterConfig;

void dispMessage(char *param, const char *msg);
MsgType determineWarnType(float value, float lowerLimitTol, float upperLimitTol);
MsgType checkIfValueApproachingLimits(float value, ParameterConfig *param);
MsgType checkIfValueWithinLimits(float value, ParameterConfig *param);
int batteryIsOk(float temperature, float soc, float chargeRate);

#endif
