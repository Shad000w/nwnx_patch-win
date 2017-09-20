#ifndef _CTLKTABLE_H_
#define _CTLKTABLE_H_

struct CTlkTableToken
{
    unsigned long m_nHash;
    CExoString m_sToken;
    unsigned long m_nActionCode;
    unsigned long m_nStrRef[4];
    unsigned long m_nStrRefDefault;
};

struct CTlkTableTokenCustom
{
    unsigned int m_nNumber;
    CExoString m_sValue;
};


struct CTlkTable_s
{
    void** m_vtable;
    int/*CTlkFile*/* m_pTlkFile[2];
    int/*CTlkFile*/* m_pTlkFileAlternate[2];
    unsigned char m_currentGender;
    CTlkTableToken* m_pTokens;
    unsigned long m_nTokens;
    CTlkTableTokenCustom* m_pTokensCustom;
    unsigned long m_nTokensCustom;
    int m_bRemove;

	int ClearCustomTokens();
	int CloseFileAlternate();
	//int CloseFile(CTlkFile **);
	int ExoIsDBCSLeadByte(unsigned char);
	//int FetchInternal(unsigned long, STR_RES &, int);
	int GetLanguageVersion();
	int GetSimpleString(unsigned long);
	//int GetTokenValue(CTlkTableToken const &, CExoString &);
	int OpenFileAlternate(CExoString const &);
	int OpenFile(CExoString);
	//int OpenFile(CExoString const &, CTlkFile **);
	int ParseStr(CExoString &);
	int RemapFontName(char *);
	int SetCustomToken(int, CExoString const &);
	int SetUseLargeDialogFont(int);
	~CTlkTable_s();
	CTlkTable_s();
	CExoString const &GetCustomTokenValue(unsigned long token_number);
};
#endif