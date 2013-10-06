#ifndef STUMPLESS_PRIVATE_VALUE_PROFILE_INITIALIZER_H
#define STUMPLESS_PRIVATE_VALUE_PROFILE_INITIALIZER_H

#include "private/type.h"

ValueProfile *
InitializeBooleanArrayValueProfile
( void );

ValueProfile *
InitializeBooleanValueProfile
( void );

ValueProfile *
InitializeCharArrayValueProfile
( void );

ValueProfile *
InitializeCharValueProfile
( void );

ValueProfile *
InitializeFloatArrayValueProfile
( void );

ValueProfile *
InitializeFloatValueProfile
( void );

ValueProfile *
InitializeDoubleArrayValueProfile
( void );

ValueProfile *
InitializeDoubleValueProfile
( void );

ValueProfile *
InitializeIntArrayValueProfile
( void );

ValueProfile *
InitializeIntValueProfile
( void );

ValueProfile *
InitializeLongArrayValueProfile
( void );

ValueProfile *
InitializeLongValueProfile
( void );

ValueProfile *
InitializeLongDoubleArrayValueProfile
( void );

ValueProfile *
InitializeLongDoubleValueProfile
( void );

ValueProfile *
InitializeLongLongArrayValueProfile
( void );

ValueProfile *
InitializeLongLongValueProfile
( void );

ValueProfile *
InitializeShortArrayValueProfile
( void );

ValueProfile *
InitializeShortValueProfile
( void );

ValueProfile *
InitializeSignedCharArrayValueProfile
( void );

ValueProfile *
InitializeSignedCharValueProfile
( void );

ValueProfile *
InitializeStringArrayValueProfile
( void );

ValueProfile *
InitializeStringValueProfile
( void );

ValueProfile *
InitializeUnsignedCharArrayValueProfile
( void );

ValueProfile *
InitializeUnsignedCharValueProfile
( void );

ValueProfile *
InitializeUnsignedIntArrayValueProfile
( void );

ValueProfile *
InitializeUnsignedIntValueProfile
( void );

ValueProfile *
InitializeUnsignedLongArrayValueProfile
( void );

ValueProfile *
InitializeUnsignedLongValueProfile
( void );

ValueProfile *
InitializeUnsignedLongLongArrayValueProfile
( void );

ValueProfile *
InitializeUnsignedLongLongValueProfile
( void );

ValueProfile *
InitializeUnsignedShortArrayValueProfile
( void );

ValueProfile *
InitializeUnsignedShortValueProfile
( void );

Status *
InitializeValueProfileByName
( const char * );

#endif
