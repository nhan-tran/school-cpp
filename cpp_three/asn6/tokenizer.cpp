

//
// Tokenizing class
//
// Michael Hoffman
//
// File: tokenizer.cpp
//
//
// Given a string, this class will break it up into
// individual tokens based on whitespace.
//


#define  _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include  <cstring>
#include  "tokenizer.h"

using  namespace  std;


#define  TOK_SEPARATORS  " \t\n"


//
// Constructor
//
// Copies the client's string into a dynamically allocated buffer.
// This is done because the tokenizing process actually modifies
// the string, so we don't want to modify the client's data.
// The first token in the string is also determined. The Error::alloc_
// exception is thrown if memory allocation fails.
//
Tokenizer::Tokenizer( const  string  &str )
{
  size_t  memSize  =  str.length() + 1;

  //
  // Allocate
  //
  m_str  =  new  char[memSize];


  //
  // Check for successful memory allocation
  //
  if  (! m_str)  throw  alloc_;

  //
  // Copy the client's string
  //
  strcpy( m_str, str.c_str() );


  //
  // Get a pointer to the first token
  //
  m_nextTok  =  strtok( m_str, TOK_SEPARATORS );
}


//
// Destructor
//
Tokenizer::~Tokenizer()
{
  //
  // Clean up allocated memory
  //
  delete  []  m_str;
 
}


//
// nextToken()
//
// Returns a pointer to the next token. If there is no
// next token, the Error::noToken_ exception is thrown.
//
string  Tokenizer::nextToken()  const
{
  //
  // If there's no "next" token, throw an exception
  //
  if  (! m_nextTok.length() )  throw  noToken_;


  //
  // tok points to the token and then m_nextTok is
  // set to the next token.
  //
  string  tok  =  m_nextTok;

  const char  *next  =  strtok( 0, TOK_SEPARATORS );

  if  (next)
    m_nextTok  =  next;
  else
    m_nextTok.clear();


  return  tok;
}


//
// done()
//
// Returns true if there is NOT a "next token", false if there
// is.
//
bool  Tokenizer::done()  const
{
  return  m_nextTok.length() == 0;
}