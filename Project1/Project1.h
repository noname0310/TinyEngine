// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the PROJECT1_EXPORTS
// symbol defined on the command line. This symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// PROJECT1_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#ifdef PROJECT1_EXPORTS
#define PROJECT1_API __declspec(dllexport)
#else
#define PROJECT1_API __declspec(dllimport)
#endif

// This class is exported from the dll
class PROJECT1_API CProject1 {
public:
	CProject1(void);
	// TODO: add your methods here.
};

extern PROJECT1_API int nProject1;

PROJECT1_API int fnProject1(void);
