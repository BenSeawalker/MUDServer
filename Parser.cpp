#include "Parser.h"


#define MIN(a, b) (((a) < (b)) ? (a) : (b));


Parser::Parser(const char ** _verbs, const char ** _nouns, const char ** _conjunctions, const char ** _articles, UINT _verbSize, UINT _nounSize, UINT _conjSize, UINT _artiSize)
	: m_verbs(_verbs), m_nouns(_nouns), m_conjs(_conjunctions), m_artis(_articles),
	m_verb_size(_verbSize), m_noun_size(_nounSize), m_conj_size(_conjSize), m_arti_size(_artiSize)
{}


Parser::~Parser()
{
	
}


/*****************************************************************************
*	PUBLIC FUNCTIONS
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// 
/////

UINT Parser::ParseSentence(Word ** _words, const char * _sentence)
{
	char ** split_str;
	UINT num_tokens = Split(&split_str, _sentence);

	*_words = new Word[num_tokens];
	
	for (UINT i = 0; i < num_tokens; i++)
	{
		// the word itself
		strcpy_s((*_words)[i].word, split_str[i]);

		//word type
		if (IsVerb((*_words)[i].word))
			(*_words)[i].type = VERB;
		else if (IsNoun((*_words)[i].word))
			(*_words)[i].type = NOUN;
		else if (IsConj((*_words)[i].word))
			(*_words)[i].type = CONJ;
		else if (IsArti((*_words)[i].word))
			(*_words)[i].type = ARTI;
		else
			(*_words)[i].type = NONE;
	}

	// cleanup
	for (UINT i = 0; i < num_tokens; i++)
		delete[] split_str[i];
	delete[] split_str;

	//return
	return num_tokens;
}


UINT Parser::Split(char *** _result, const char * _str, char _c)
{
	UINT num_tokens = count(_str, _str + strlen(_str), _c) + 1;
	*_result = new char *[num_tokens];

	UINT t = 0;
	do
	{
		const char * begin = _str;

		while (*_str != _c && *_str )
			_str++;

		UINT t_size = MIN(((_str - begin) + 1), MAX_WORD_LENGTH);
		char * token = new char[t_size]();
		for (UINT i = 0; i < t_size-1; i++)
			token[i] = *(begin++);

		(*_result)[t++] = token;
	} while (0 != *_str++);

	return num_tokens;
}



/*****************************************************************************
*	PRIVATE FUNCTIONS
*****************************************************************************/

//////////////////////////////////////////////////////////////////////////////
// 
/////

bool Parser::IsVerb(const char * _word)
{
	return (FindStrIn(_word, m_verbs, m_verb_size) > -1);
}
bool Parser::IsNoun(const char * _word)
{
	return (FindStrIn(_word, m_nouns, m_noun_size) > -1);
}
bool Parser::IsConj(const char * _word)
{
	return (FindStrIn(_word, m_conjs, m_conj_size) > -1);
}
bool Parser::IsArti(const char * _word)
{
	return (FindStrIn(_word, m_artis, m_arti_size) > -1);
}

int Parser::FindStrIn(const char * _str, const char ** _lst, const UINT _lstSize)
{
	bool found = false;
	UINT index;

	for (index = 0; index < _lstSize && !found; index++)
		found = (_stricmp(_str, _lst[index]) == 0);

	return (found ? index : -1);
}