//
//  NBPhoneNumberManager.h
//  Band
//
//  Created by ishtar on 12. 12. 11..
//  Copyright (c) 2012년 NHN. All rights reserved.
//

#import <Foundation/Foundation.h>

#pragma mark - Enum -
typedef enum {
    E164 = 0,
    INTERNATIONAL = 1,
    NATIONAL = 2,
    RFC3966 = 3
} NBEPhoneNumberFormat;

typedef enum {
    FIXED_LINE = 0,
    MOBILE = 1,
    // In some regions (e.g. the USA), it is impossible to distinguish between
    // fixed-line and mobile numbers by looking at the phone number itself.
    FIXED_LINE_OR_MOBILE = 2,
    // Freephone lines
    TOLL_FREE = 3,
    PREMIUM_RATE = 4,
    // The cost of this call is shared between the caller and the recipient, and
    // is hence typically less than PREMIUM_RATE calls. See
    // http://en.wikipedia.org/wiki/Shared_Cost_Service for more information.
    SHARED_COST = 5,
    // Voice over IP numbers. This includes TSoIP (Telephony Service over IP).
    VOIP = 6,
    // A personal number is associated with a particular person, and may be routed
    // to either a MOBILE or FIXED_LINE number. Some more information can be found
    // here = http://en.wikipedia.org/wiki/Personal_Numbers
    PERSONAL_NUMBER = 7,
    PAGER = 8,
    // Used for 'Universal Access Numbers' or 'Company Numbers'. They may be
    // further routed to specific offices, but allow one number to be used for a
    // company.
    UAN = 9,
    // Used for 'Voice Mail Access Numbers'.
    VOICEMAIL = 10,
    // A phone number is of type UNKNOWN when it does not fit any of the known
    // patterns for a specific region.
    UNKNOWN = -1
} NBEPhoneNumberType;


typedef enum {
    NOT_A_NUMBER = 0,
    NO_MATCH = 1,
    SHORT_NSN_MATCH = 2,
    NSN_MATCH = 3,
    EXACT_MATCH = 4
} NBEMatchType;


typedef enum {
    IS_POSSIBLE = 0,
    INVALID_COUNTRY_CODE = 1,
    TOO_SHORT = 2,
    TOO_LONG = 3
} NBEValidationResult;

@class NBPhoneMetaData, NBPhoneNumber;

@interface NBPhoneNumberManager : NSObject

+ (NBPhoneNumberManager*)sharedInstance;

- (NSString*)numbersOnly:(NSString*)phoneNumber;

- (NSArray*)regionCodeFromCountryCode:(NSString*)countryCodeNumber;
- (NSString*)countryCodeFromRregionCode:(NSString*)regionCode;


// functions

- (BOOL)isNumberGeographical:(NBPhoneNumber*)phoneNumber;

- (NBPhoneNumber*)getExampleNumber:(NSString*)regionCode;
- (NBPhoneNumber*)getExampleNumberForType:(NSString*)regionCode type:(NBEPhoneNumberType)type;
- (NBPhoneNumber*)getExampleNumberForNonGeoEntity:(NSString*)countryCallingCode;

- (NBPhoneMetaData*)getMetadataForRegion:(NSString*)regionCode;
- (NBPhoneMetaData*)getMetadataForNonGeographicalRegion:(NSString*)countryCallingCode;

- (NSString*)getNationalSignificantNumber:(NBPhoneNumber*)phoneNumber;
- (BOOL)isLeadingZeroPossible:(NSString*)countryCallingCode;
- (int)getLengthOfGeographicalAreaCode:(NBPhoneNumber*)phoneNumber;
- (int)getLengthOfNationalDestinationCode:(NBPhoneNumber*)phoneNumber;
- (NSString*)convertAlphaCharactersInNumber:(NSString*)number;

- (NSString*)normalizePhoneNumber:(NSString*)phoneNumber;
- (NSString*)normalizeDigitsOnly:(NSString*)number;

- (NSString*)format:(NBPhoneNumber*)phoneNumber numberFormat:(NBEPhoneNumberFormat)numberFormat;
- (NSString*)formatOutOfCountryCallingNumber:(NBPhoneNumber*)number regionCallingFrom:(NSString*)regionCallingFrom;
- (NSString*)formatOutOfCountryKeepingAlphaChars:(NBPhoneNumber*)number regionCallingFrom:(NSString*)regionCallingFrom;
- (NSString*)formatNationalNumberWithCarrierCode:(NBPhoneNumber*)number carrierCode:(NSString*)carrierCode;
- (NSString*)formatNationalNumberWithPreferredCarrierCode:(NBPhoneNumber*)number fallbackCarrierCode:(NSString*)fallbackCarrierCode;

@end
