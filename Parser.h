#pragma once

typedef unsigned int UINT;

#include <algorithm>
using std::count;

#include "GameData.h"
using namespace GameData;

class Parser
{
public:
	Parser(const char ** _verbs = Verbs, const char ** _nouns = Nouns, const char ** _conjunctions = Conjunctions, const char ** _articles = Articles,
		UINT _verbSize = VerbSize, UINT _nounSize = NounSize, UINT _conjSize = ConjSize, UINT _artiSize = ArtiSize);
	~Parser();

	UINT ParseSentence(Word ** _words, const char * _sentence);

	//UINT TokenizeString(char ** _tokens, char * _src, char * _delims);

	static UINT Split(char *** _result, const char * _str, char _c = ' ');


private:
	const char ** m_verbs;
	const char ** m_nouns;
	const char ** m_conjs;
	const char ** m_artis;

	const UINT m_verb_size;
	const UINT m_noun_size;
	const UINT m_conj_size;
	const UINT m_arti_size;


	bool IsVerb(const char * _word);
	bool IsNoun(const char * _word);
	bool IsConj(const char * _word);
	bool IsArti(const char * _word);

	int FindStrIn(const char * _str, const char ** _lst, const UINT _lstSize);
};
