#ifndef __STUMPLESS_PRIVATE_VALUE_PROFILE_INITIALIZER_H
#define __STUMPLESS_PRIVATE_VALUE_PROFILE_INITIALIZER_H

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

Exception *
InitializeValueProfileByName
( const char * );

/**
 * @private
 * Creates the ValueProfile for void pointer arrays. The name of the profile is
 * "void array".
 *
 * @return the ValueProfile for void pointer arrays.
 */
ValueProfile *
InitializeVoidArrayValueProfile
( void );

/**
 * @private
 * Creates the ValueProfile for void pointers. The name of the profile is
 * "void".
 *
 * @return the ValueProfile for void pointers.
 */
ValueProfile *
InitializeVoidValueProfile
( void );

#endif
