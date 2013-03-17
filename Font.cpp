// Font.cpp: implementation of the Font class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Font.h"
#include "GameProc.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFont::CFont( char *szFontFile, int char_width, int char_height, int color_key )
{


	SDL_Surface *pTemp;
	char buf[255];

	m_charWidth = char_width;
	m_charHeight = char_height;

	if ( (pTemp = SDL_LoadBMP( szFontFile ) ) == NULL )
	{
		sprintf( buf, "Failed to load font - %s", szFontFile );
		VampireIvo::LOG( string(buf) );
		return;
	}

	// set color key
	if ( color_key != -1 )
	{
		SDL_SetColorKey( pTemp, SDL_SRCCOLORKEY, color_key );
	}

	// get dimensions
	SDL_Rect rect;
	SDL_GetClipRect( pTemp, &rect );
	m_imgWidth = rect.w;
	m_imgHeight = rect.h;

	m_pImage = SDL_DisplayFormat( pTemp );

	sprintf( buf, "Loaded font - %s", szFontFile );
	VampireIvo::LOG( string(buf) );
}


CFont::~CFont()
{

}


void CFont::Destroy()
{
	SDL_FreeSurface( m_pImage );
}


void CFont::BlitText( int x, int y, char *szText, SDL_Surface *pScreen )
{

	char *p = szText;
	int n = strlen( p );
	bool bBlit = false;
	SDL_Rect rsrc, rdst;

	while( (n--) > 0 )
	{
		if ( (*p >= 'A' && *p <= 'Z') )
		{
			rsrc.x = (*p - 'A') * m_charWidth;
			rsrc.y = 0;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}
		else if ( *p >= '0' && *p <= '9')
		{
			rsrc.x = (*p - '0') * m_charWidth;
			rsrc.y = m_charHeight;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}
		else if ( *p == ':' )
		{
			rsrc.x = m_charWidth * 10;
			rsrc.y = m_charHeight;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}
		else if ( *p == '%' )
		{
			rsrc.x = m_charWidth * 11;
			rsrc.y = m_charHeight;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}
		else if ( *p == ' ' )
		{
			rsrc.x = m_charWidth * 13;
			rsrc.y = m_charHeight;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}
		else if ( *p == '/' )
		{
			rsrc.x = m_charWidth * 12;
			rsrc.y = m_charHeight;
			rsrc.w = m_charWidth;
			rsrc.h = m_charHeight;
			bBlit = true;
		}


		if ( bBlit )
		{
			rdst.x = x;
			rdst.y = y;
			rdst.w = m_charWidth;
			rdst.h = m_charHeight;

			SDL_BlitSurface( m_pImage, &rsrc, pScreen, &rdst );

			x += m_charWidth;		

			bBlit = false;
		}


		p++;
	}


}
