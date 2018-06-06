/******************************************************************************************
 *	Chili DirectX Framework Version 16.07.20											  *
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"
#include "FrameTimer.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	std::ifstream in( "_Configuration_.txt" );
	assert( "Configuration file not found!" && in.good() );

	const std::string fullFile = ReadFile( in );
	auto b = fullFile;
	
	const auto& ff = fullFile;
	typedef const int cint;
	cint xStart = GetData( "X Start",ff );
	cint yStart = GetData( "Y Start",ff );
	cint frameWidth = GetData( "Frame Width",ff );
	cint frameHeight = GetData( "Frame Height",ff );
	cint nFrames = GetData( "Number of Frames",ff );
	cint holdTime = GetData( "Frames per Second",ff );
	assert( "FPS cannot be 0!" && holdTime != 0 );

	thePlayer = new Anim( xStart,yStart,
		frameWidth,frameHeight,
		nFrames,spriteSheet,
		1.0f / float( holdTime ) );
}

Game::~Game()
{
	delete( thePlayer );
}

void Game::Go()
{
	gfx.BeginFrame();
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	thePlayer->Update( FrameTimer::Mark() );
}

std::string Game::ReadFile( std::ifstream& in )
{
	std::string temp;
	for( char c = in.get(); in.good(); c = in.get() )
	{
		temp += c;
	}
	return( temp );
}

int Game::GetData( const std::string& name,
	const std::string& src,
	const std::string& delimiter )
{
	const int pos = int( src.find( name ) + name.size() );
	const int addAmount = pos + int( delimiter.size() );
	assert( pos != -1 );
	assert( src[addAmount] != '\n' );
	
	std::string start = "";
	int i = 0;
	while( src[addAmount + i] != '\n' )
	{
		start += src[addAmount + i];
		++i;
	}

	auto b = start;
	
	return( std::stoi( start ) );
}

void Game::ComposeFrame()
{
	thePlayer->Draw( Vei2( 15,15 ),gfx );
}
