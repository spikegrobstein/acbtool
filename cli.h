// helpful macros:

#define QQ(s) #s
#define OPT_SHORT(OPTION)	OPT_ ## OPTION ## _SHORT
#define OPT_LONG(OPTION) OPT_ ## OPTION ## _LONG
#define OPT_ROW(OPTION,ARG_1,ARG_2) { OPT_ ## OPTION ## _LONG, ARG_1, ARG_2, OPT_ ## OPTION ## _SHORT }

//common options:

#define OPT_VERBOSE_SHORT							'v'
#define OPT_VERBOSE_LONG							"verbose"
//#define OPT_VERBOSE_ROW								{ OPT_VERBOSE_LONG, no_argument, NULL, OPT_VERBOSE_SHORT }
#define OPT_VERBOSE_HELP							"Increase level of verbosity"

#define OPT_SUPPRESS_HEADERS_SHORT		'S'
#define OPT_SUPPRESS_HEADERS_LONG			"suppress-headers"
//#define OPT_SUPPRESS_HEADERS_ROW			{ OPT_SUPPRESS_HEADERS_LONG, no_argument, NULL, OPT_SUPPRESS_HEADERS_SHORT }
#define OPT_SUPPRESS_HEADERS_HELP			"Suppress column headers and row labels on output (simplify scripting)"

#define OPT_QUIET_SHORT								'q'
#define OPT_QUIET_LONG								"quiet"
//#define OPT_QUIET_ROW									{ OPT_QUIET_LONG, no_argument, NULL, OPT_QUIET_SHORT }
#define OPT_QUIET_HELP								"don't output anything"

#define OPT_HEX_SHORT									'x'
#define OPT_HEX_LONG									"hex"
//#define OPT_HEX_ROW										{ OPT_HEX_LONG, no_argument, NULL, OPT_HEX_SHORT }
#define OPT_HEX_HELP									"output numerical values as hex"

// options that are common between all actions
#define COMMON_OPTIONS								OPT_ROW(VERBOSE, no_argument, NULL), \
																			OPT_ROW(SUPPRESS_HEADERS, no_argument, NULL), \
																			OPT_ROW(QUIET, no_argument, NULL), \
																			OPT_ROW(HEX, no_argument, NULL)


// other definitions:

#define OPT_HEADER_ONLY_SHORT					'H'
#define OPT_HEADER_ONLY_LONG					"header-only"
#define OPT_HEADER_ONLY_HELP					"Only output the header portion of the acb file"