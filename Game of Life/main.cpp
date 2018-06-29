#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <stdlib.h>
#include <Windows.h>
#include <string>
#include <cmath>
#include <time.h>
#include "life.h"
#include "button.h"

///MAIN
int main(){

    int cell_size = 10; ///Must be divisible by 720
    /// Any 4:3 resolution
    int x = 960; ///960
    int y = 720; ///720
    int cell_no = y*y/cell_size;
    int cell_border = 1;

    int tick_mod = 200;
    clock_t ticks;
    int move_tick = tick_mod;
    int pause_tick = tick_mod;
    int update_tick = tick_mod;
    bool paused = false;
    bool mouseLDown = false;

    // create the window
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;
    sf::RenderWindow window(sf::VideoMode(x, y), "Always look on the bright-side of life",sf::Style::Close, settings);
    int charSize = (window.getSize().x)/64;


    sf::Color bckgrd = sf::Color::Black;
    sf::Color col_live = sf::Color::Yellow;
    sf::Color col_dead = sf::Color(128,128,128); /// Gray

    sf::RectangleShape panel;
    panel.setPosition(sf::Vector2f(y,0));
    panel.setSize(sf::Vector2f(x-y,y));
    panel.setFillColor(sf::Color(128,128,128));

    sf::Font font;
    if(!font.loadFromFile("consola.ttf")){
        std::cout << "oh fuck main";
    }

    int offset = 0;
    int shift = 1;

    sf::Text title;
    title.setFont(font);
    title.setString("Conway's Game of Life");
    title.setCharacterSize(charSize*1.2);
    title.setFillColor(sf::Color::Yellow);
    title.setPosition(sf::Vector2f(y+charSize/2,shift*offset++));
    shift++;
    Button wrapButt(sf::Vector2f(y+charSize,charSize*shift+offset),charSize,"Toggle Wrapping",true);
    shift++;
    offset+=10;
    Button borderButt(sf::Vector2f(y+charSize,charSize*shift+offset),charSize,"Toggle No Tile Borders",true);
    shift++;
    offset+=10;
    Button resetButt(sf::Vector2f(y+charSize,charSize*shift+offset),charSize,"Reset Cells",false);
    shift++;
    offset+=10;
    sf::Text chooseCol;
    chooseCol.setFont(font);
    chooseCol.setString("Choose a cell color:");
    chooseCol.setCharacterSize(charSize);
    chooseCol.setFillColor(sf::Color::Black);
    chooseCol.setPosition(sf::Vector2f(y+charSize/2,charSize*shift+offset));
    shift++;
    offset+=10;
    Button greenButt(sf::Vector2f(y+charSize,charSize*shift+offset),charSize,"Green",false);
    sf::RectangleShape greenButtSquare;
    greenButtSquare.setPosition(sf::Vector2f(y+charSize,charSize*shift+offset));
    greenButtSquare.setSize(sf::Vector2f(charSize,charSize));
    greenButtSquare.setFillColor(sf::Color::Green);
    Button yellowButt(sf::Vector2f(y+8*charSize,charSize*shift+offset),charSize,"Yellow",false);
    sf::RectangleShape yellowButtSquare;
    yellowButtSquare.setPosition(sf::Vector2f(y+8*charSize,charSize*shift+offset));
    yellowButtSquare.setSize(sf::Vector2f(charSize,charSize));
    yellowButtSquare.setFillColor(sf::Color::Yellow);
    shift++;
    offset+=10;
    Button blueButt(sf::Vector2f(y+charSize,charSize*shift+offset),charSize,"Blue",false);
    sf::RectangleShape blueButtSquare;
    blueButtSquare.setPosition(sf::Vector2f(y+charSize,charSize*shift+offset));
    blueButtSquare.setSize(sf::Vector2f(charSize,charSize));
    blueButtSquare.setFillColor(sf::Color::Blue);
    Button redButt(sf::Vector2f(y+8*charSize,charSize*shift+offset),charSize,"Red",false);
    sf::RectangleShape redButtSquare;
    redButtSquare.setPosition(sf::Vector2f(y+8*charSize,charSize*shift+offset));
    redButtSquare.setSize(sf::Vector2f(charSize,charSize));
    redButtSquare.setFillColor(sf::Color::Red);
    shift++;
    Button pauseButt(sf::Vector2f(y+charSize,charSize*shift+offset++),charSize,"Pause",true);
    shift++;
    sf::Text pauseMsg;
    pauseMsg.setFont(font);
    pauseMsg.setString("Press SPACE to pause.");
    pauseMsg.setCharacterSize(charSize);
    pauseMsg.setFillColor(sf::Color::Black);
    pauseMsg.setPosition(sf::Vector2f(y+charSize,charSize*shift+offset++));
    shift++;
    offset++;
    sf::Text pausedTxt;
    pausedTxt.setFont(font);
    pausedTxt.setString("Paused");
    pausedTxt.setCharacterSize(charSize);
    pausedTxt.setFillColor(sf::Color::Red);
    pausedTxt.setPosition(sf::Vector2f(y+charSize,charSize*shift+offset));
    sf::Text runningTxt;
    runningTxt.setFont(font);
    runningTxt.setString("Running");
    runningTxt.setCharacterSize(charSize);
    runningTxt.setFillColor(sf::Color::Green);
    runningTxt.setPosition(sf::Vector2f(y+charSize,charSize*shift+offset));




    Life game(cell_no/y,false);

    //WinT test(&window);
    window.clear(bckgrd);
    window.display();
    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        ticks = clock();

        if (ticks - pause_tick > tick_mod && sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && window.hasFocus()){
            paused = !paused;
            pause_tick = clock();
        }

        if(ticks - move_tick > tick_mod && !paused){ ///ticks%(tick_mod*1) == 0
            game.refreshWorld();
            move_tick = clock();
        }


        std::vector<std::vector<sf::FloatRect> > cellBounds;

        for(int k = 0; k < game.getDim(); k++){
            std::vector<sf::FloatRect> rowBounds;
            for(int j = 0; j < game.getDim(); j++){
                sf::RectangleShape cell(sf::Vector2f(cell_size-cell_border,cell_size-cell_border));
                cell.setPosition(k*cell_size,j*cell_size);
                rowBounds.push_back(cell.getGlobalBounds());
                if(game.getCell(k,j)){
                    cell.setFillColor(col_live);
                }
                else{
                    cell.setFillColor(col_dead);
                }
                window.draw(cell);
            }
            cellBounds.push_back(rowBounds);
        }

        if(ticks - update_tick > 2*tick_mod){ ///ticks%(tick_mod*1) == 0
            sf::Vector2i ipos = sf::Mouse::getPosition(window);
            sf::Vector2f pos(ipos.x,ipos.y);
            /// Collision for life
            for(int k = 0; k < game.getDim(); k++){
                for(int j = 0; j < game.getDim(); j++){
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Left) && cellBounds[k][j].contains(pos) && window.hasFocus()){
                        game.modCell(k,j,true);
                    }
                    if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && cellBounds[k][j].contains(pos) && window.hasFocus()){
                        game.modCell(k,j,false);
                    }
                }
            }
            /// Collision for buttons
            if(!mouseLDown && sf::Mouse::isButtonPressed(sf::Mouse::Left) && window.hasFocus()){
                //std::cout << "MouseButtonPressed Caught!" << std::endl;
                if(wrapButt.check(pos)){
                    wrapButt.trigger();
                    game.wrap = wrapButt.getState();
                    //std::cout << "wrap" << std::endl;
                }

                if(borderButt.check(pos)){
                    borderButt.trigger();
                    if(borderButt.getState()){
                        cell_border = 0;
                        col_dead = sf::Color::Black;
                        //std::cout << "black" << std::endl;
                    }
                    else{
                        cell_border = 1;
                        window.clear(bckgrd); /// Surprisingly isn't terrible, but keep an eye on it.
                        col_dead = sf::Color(128,128,128);
                        //std::cout << "grey" << std::endl;
                    }
                }

                if(resetButt.check(pos)){
                    resetButt.trigger();
                    if(resetButt.getState()){
                        game.clearWorld();
                    }
                }

                if(greenButt.check(pos)){
                    greenButt.trigger();
                    if(greenButt.getState()){
                        col_live = sf::Color::Green;
                    }
                }

                if(yellowButt.check(pos)){
                    yellowButt.trigger();
                    if(yellowButt.getState()){
                        col_live = sf::Color::Yellow;
                    }
                }

                if(blueButt.check(pos)){
                    blueButt.trigger();
                    if(blueButt.getState()){
                        col_live = sf::Color::Blue;
                    }
                }

                if(redButt.check(pos)){
                    redButt.trigger();
                    if(redButt.getState()){
                        col_live = sf::Color::Red;
                    }
                }
            }

            if(!mouseLDown && sf::Mouse::isButtonPressed(sf::Mouse::Left)){
                //std::cout << "MouseButtonPressed Caught!" << std::endl;

                //std::cout << cell_border << std::endl;
            }




            /// check if left mouse button is down
            mouseLDown = sf::Mouse::isButtonPressed(sf::Mouse::Left);
            //std::cout << mouseLDown << std::endl;
        }

        /// draw everything here...
        window.draw(panel);
        window.draw(title);
        window.draw(chooseCol);
        wrapButt.draw(&window);
        borderButt.draw(&window);
        greenButt.draw(&window);
        window.draw(greenButtSquare);
        yellowButt.draw(&window);
        window.draw(yellowButtSquare);
        redButt.draw(&window);
        window.draw(redButtSquare);
        blueButt.draw(&window);
        window.draw(blueButtSquare);
        resetButt.draw(&window);
        window.draw(pauseMsg);
        if(paused){
            window.draw(pausedTxt);
        }else{
            window.draw(runningTxt);
        }

        window.display();
        //Sleep(100);
    }

    return 0;



}
