// Sprite.cpp: implementation of the CSprite class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Sprite.h"
#include "GameProc.h"


namespace VampireIvo {

extern int g_magenta;


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CSprite::CSprite( char **lpszFilePaths, int num_frames, int color_key, bool bMakeMask )
{
	char buf[255];


	// init
	m_pMask = NULL;
	m_numframes = num_frames;
	m_curframe = 0;
	m_bMask = bMakeMask;
	////////////////

	VampireIvo::LOG( "Loading sprite..." );

	// alloc mem
	m_pImages = (SDL_Surface **) new SDL_Surface[num_frames];
	if ( m_pImages == NULL )
	{
		VampireIvo::LOG( "Could not allocate memory for sprite images!" );
		return;
	}

	m_pMask = (int **) new int[num_frames];
	if ( m_pMask == NULL )
	{
		VampireIvo::LOG( "Could not allocate memory for sprite masks!" );
		return;
	}


	m_pWidths = new int[num_frames];
	m_pHeights = new int[num_frames];


	for( int i = 0; i < m_numframes; i++ )
	{
		SDL_Surface *pTemp;

		if ( (pTemp = SDL_LoadBMP( lpszFilePaths[i] ) ) == NULL )
		{
			sprintf( buf, "Failed to load image - %s", lpszFilePaths[i] );
			VampireIvo::LOG( string(buf) );
			return;
		}

		// set color key
		if ( color_key != -1 )
		{
			SDL_SetColorKey( pTemp, SDL_SRCCOLORKEY, color_key );
		}

		// get dimensions
		m_pWidths[i] = pTemp->w;
		m_pHeights[i] = pTemp->h;
		m_pImages[i] = SDL_DisplayFormat( pTemp );

		SDL_FreeSurface( pTemp );
		
		//  create mask for surface
		if ( m_bMask )
		{
			sprintf( buf, "Creating bool Mask for - %s", lpszFilePaths[i] );
			VampireIvo::DBG( string(buf) );
			VampireIvo::MakeBoolMask( m_pImages[i], m_pMask[i], VampireIvo::g_magenta );
		}
		
		sprintf( buf, "Loaded image - %s", lpszFilePaths[i] );
		VampireIvo::LOG( string(buf) );

		
	}

	VampireIvo::LOG( "Loading sprite...OK!" );
	
}


void CSprite::Destroy()
{
	VampireIvo::LOG( "Releasing sprite..." );

	for( int i = 0; i < m_numframes; i++ )
	{
		SDL_FreeSurface( m_pImages[i] );
		if ( m_bMask )
			delete m_pMask[i];
	}


	delete[] m_pImages;
	if ( m_bMask )
		delete[] m_pMask;
	delete[] m_pWidths;
	delete[] m_pHeights;
	

	VampireIvo::LOG( "Releasing sprite...OK!" );

}


void CSprite::Update( int x, int y, int curframe, SDL_Surface *pScreen )
{

	m_curframe = curframe;

	SDL_Rect dest_rect;
	dest_rect.x = x;
	dest_rect.y = y;

	SDL_Rect surf_rect;
	VampireIvo::SetRect( &surf_rect, 0, 0, m_pWidths[curframe], m_pHeights[curframe] );

	VampireIvo::ClipRect( &x, &y, &surf_rect );
	SDL_BlitSurface( m_pImages[curframe], NULL, pScreen, &dest_rect );

}


CSprite::~CSprite()
{

}


int* CSprite::getMask() 
{ 
	if ( m_bMask )
	{
		return m_pMask[m_curframe]; 
	}
	else
	{
		return NULL;
	}
};


} //end namespace