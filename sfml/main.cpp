#include<SFML/Graphics.hpp>
#include<vector>
#include<iostream>
#include<thread>
#include<chrono>
#include<algorithm>
#include<iterator>

//Global variables
int lvl = 0;
int plateWidth = 160;
int plateWidthDif = 10;
int plateHeight = 655;
int plateHeightDif = 25;
int rodLPos = 80;
int rodCPos = 280;
int rodRPos = 480;

int hLvlL{};
int hLvlC{};
int hLvlR{};

int sizeL{};
int sizeC{};
int sizeR{};

extern int globalCounter{};
extern int from[100]{};
extern int to[100]{};

void hanoi(float n, char A, char B, char C)
{
    // moves n plates from A to C using B as buffer
    if (n > 0)
    {       
        hanoi(n - 1, A, C, B);

        std::cout << globalCounter << ": " << A << " -> " << C << "\n";
        if (A == 'A')
            from[globalCounter] = 1;
        else if(A == 'B')
            from[globalCounter] = 2;
        else if(A == 'C')
            from[globalCounter] = 3;

        if (C == 'A')
            to[globalCounter] = 1;
        else if (C == 'B')
            to[globalCounter] = 2;
        else if (C == 'C')
            to[globalCounter] = 3;

        ++globalCounter;
        hanoi(n - 1, B, A, C);     
    }
}

int main()
{
    //for (size_t i = 0; i < 100; i++) //prints all moves
    //    std::cout << i << ": " << from[i] << "-" << to[i] << std::endl;

    sf::RenderWindow window(sf::VideoMode(600, 720), "Tower of Hanoi"); window.setFramerateLimit(60);

    sf::RectangleShape base;
    base.setSize(sf::Vector2f(600, 40)); base.setFillColor(sf::Color(54, 45, 5, 255)); base.setPosition(0, 680);

    sf::RectangleShape rodL;
    rodL.setSize(sf::Vector2f(40, 440)); rodL.setFillColor(sf::Color(81, 68, 5, 255));rodL.setPosition(rodLPos, 240);
    sf::RectangleShape rodC = rodL;rodC.setPosition(rodCPos, 240);sf::RectangleShape rodR = rodL;
    rodR.setPosition(rodRPos, 240);

    std::vector<sf::RectangleShape> plates; sf::RectangleShape plate;

    std::vector<sf::RectangleShape> vrodL;std::vector<sf::RectangleShape> vrodC;std::vector<sf::RectangleShape> vrodR;

    //User decide how many plates there will be
    float n{};
    long long speed{};

    std::cout << "Ile krazkow: ";
    std::cin >> n;
    std::cout << "Podaj predkosc: [1000 - 1s]";
    std::cin >> speed;

    hLvlL = n;
    sizeL = n;
    hanoi(n, 'A', 'B', 'C');

   for (size_t i = 0; i < n; i++)
    {
       plate.setSize(sf::Vector2f(plateWidth - (i * plateWidthDif), 20));
       plate.setOrigin(plate.getSize().x / 2 - 20, 0); 
       plate.setPosition(rodLPos, plateHeight - (i * plateHeightDif));
       plate.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

       plates.push_back(sf::RectangleShape(plate));
       vrodL.push_back(sf::RectangleShape(plate));
    }

   int e{};
   int totalMoves = pow(2, n) - 1;
   sizeL = n;

   n--;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                window.close();
        }

        //Update        
        std::this_thread::sleep_for(std::chrono::milliseconds(speed));
        
        if (totalMoves != 0)
        {             
            std::cout << vrodL.size() << " | ";
            std::cout << vrodC.size() << " | ";
            std::cout << vrodR.size() << std::endl;

            if (from[e] == 1 && to[e] == 2)  // L -> C
            {
                vrodC.push_back(vrodL[sizeL - 1]);
                sizeL--;
                sizeC++;
                vrodC[sizeC - 1].setPosition(rodCPos, plateHeight - (hLvlC * 25));
                hLvlC++;
                hLvlL--;
                vrodL.pop_back();
            }

            else if (from[e] == 1 && to[e] == 3) // L -> R
            {
                vrodR.push_back(vrodL[sizeL - 1]);
                sizeL--;
                sizeR++;
                vrodR[sizeR - 1].setPosition(rodRPos, plateHeight - (hLvlR * 25));
                hLvlR++;
                hLvlL--;
                vrodL.pop_back();
            }

            else if (from[e] == 2 && to[e] == 1)  // C -> L
            {
                vrodL.push_back(vrodC[sizeC - 1]);
                sizeC--;
                sizeL++;
                vrodL[sizeL - 1].setPosition(rodLPos, plateHeight - (hLvlL * 25));
                hLvlL++;
                hLvlC--;
                vrodC.pop_back();
            }

            else if (from[e] == 2 && to[e] == 3)  // C -> R
            {
                vrodR.push_back(vrodC[sizeC - 1]);
                sizeC--;
                sizeR++;
                vrodR[sizeR - 1].setPosition(rodRPos, plateHeight - (hLvlR * 25));
                hLvlR++;
                hLvlC--;
                vrodC.pop_back();
            }

            else if (from[e] == 3 && to[e] == 1)  // R -> L
            {
                vrodL.push_back(vrodR[sizeR - 1]);
                sizeR--;
                sizeL++;
                vrodL[sizeL - 1].setPosition(rodLPos, plateHeight - (hLvlL * 25));
                hLvlL++;
                hLvlR--;
                vrodR.pop_back();
            }

            else if(from[e] == 3 && to[e] == 2)  // R -> C
            {
                vrodC.push_back(vrodR[sizeR - 1]);
                sizeR--;
                sizeC++;
                vrodC[sizeC - 1].setPosition(rodCPos, plateHeight - (hLvlC * 25));
                hLvlC++;
                hLvlR--;
                vrodR.pop_back();
            }
            totalMoves--;
            e++;
        }
        
        //Render
        window.clear();

        window.draw(base);
        window.draw(rodL);
        window.draw(rodC);
        window.draw(rodR);

        for (size_t i = 0; i < vrodL.size(); i++)
            window.draw(vrodL[i]);
        for (size_t i = 0; i < vrodC.size(); i++)
            window.draw(vrodC[i]);
        for (size_t i = 0; i < vrodR.size(); i++)
            window.draw(vrodR[i]);

        window.display();
    }
    return 0;
}

/*
        if (e == 0)
        {
            vrodR.push_back(vrodL[sizeL - 1]);
            sizeL--;
            sizeR++;
            vrodR[sizeR - 1].setPosition(480, 655 - (hLvlR * 25));
            hLvlR++;
            hLvlL--;
            vrodL.pop_back();
        }

        if (e == 1)
        {
            vrodC.push_back(vrodL[sizeL - 1]);
            sizeL--;
            sizeC++;
            vrodC[sizeC - 1].setPosition(280, 655 - (hLvlC * 25));
            hLvlC++;
            hLvlL--;
            vrodL.pop_back();
        }

        if (e == 2)
        {
            vrodC.push_back(vrodR[sizeR - 1]);
            sizeR--;
            sizeC++;
            vrodC[sizeC - 1].setPosition(280, 655 - (hLvlC * 25));
            hLvlC++;
            hLvlR--;
            vrodR.pop_back();
        }
        if (e == 3)
        {
            vrodR.push_back(vrodL[sizeL - 1]);
            sizeL--;
            sizeR++;
            vrodR[sizeR - 1].setPosition(480, 655 - (hLvlR * 25));
            hLvlR++;
            hLvlL--;
            vrodL.pop_back();
        }
        if (e == 4)
        {
            vrodL.push_back(vrodC[sizeC - 1]);
            sizeC--;
            sizeL++;
            vrodL[sizeL - 1].setPosition(80, 655 - (hLvlL * 25));
            hLvlL++;
            hLvlC--;
            vrodC.pop_back();
        }
        if (e == 5)
        {
            vrodR.push_back(vrodC[sizeC - 1]);
            sizeC--;
            sizeR++;
            vrodR[sizeR - 1].setPosition(480, 655 - (hLvlR * 25));
            hLvlR++;
            hLvlC--;
            vrodC.pop_back();
        }
        if (e == 6)
        {
            vrodR.push_back(vrodL[sizeL - 1]);
            sizeL--;
            sizeR++;
            vrodR[sizeR - 1].setPosition(480, 655 - (hLvlR * 25));
            hLvlR++;
            hLvlL--;
            vrodL.pop_back();
        }
        if (e == 7)
        {
            vrodL.push_back(vrodR[sizeR - 1]);
            sizeR--;
            sizeL++;
            vrodL[sizeL - 1].setPosition(80, 655 - (hLvlL * 25));
            hLvlL++;
            hLvlR--;
            vrodR.pop_back();
        }
        */


/*
if (from[e] == 1 && to[e] == 2)
            {

                vrodL[sizeL].setPosition(280, 655 - (hLvlC * 25));
                hLvlC++;
                hLvlL--;
                sizeC++;
                sizeL--;
            }

            else if (from[e] == 1 && to[e] == 3)
            {
                vrodL[sizeL].setPosition(480, 655 - (hLvlR * 25));
                hLvlR++;
                hLvlL--;
                sizeR++;
                sizeL--;
            }

            else if (from[e] == 2 && to[e] == 1)
            {
                vrodC[sizeC].setPosition(80, 655 - (hLvlL * 25));
                hLvlL++;
                hLvlC--;
                sizeL++;
                sizeC--;
            }

            else if (from[e] == 2 && to[e] == 3)
            {
                vrodC[sizeC].setPosition(480, 655 - (hLvlR * 25));
                hLvlR++;
                hLvlC--;
                sizeR++;
                sizeC--;
            }

            else if (from[e] == 3 && to[e] == 1)
            {
                vrodR[sizeR].setPosition(80, 655 - (hLvlL * 25));
                hLvlL++;
                hLvlR--;
                sizeL++;
                sizeR--;
            }

            else if(from[e] == 3 && to[e] == 2)
            {
                vrodR[sizeR].setPosition(280, 655 - (hLvlC * 25));
                hLvlC++;
                hLvlR--;
                sizeC++;
                sizeR--;
            }
*/

/*
0: 1-3
1: 1-2
2: 3-2
3: 1-3
4: 2-1
5: 2-3
6: 1-3
7: 1-2
8: 3-2
9: 3-1
10: 2-1
11: 3-2
12: 1-3
13: 1-2
14: 3-2
15: 1-3
16: 2-1
17: 2-3
18: 1-3
19: 2-1
20: 3-2
21: 3-1
22: 2-1
23: 2-3
24: 1-3
25: 1-2
26: 3-2
27: 1-3
28: 2-1
29: 2-3
30: 1-3
*/

/*if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
{
    plates[n - 1].setPosition(rodCPos, plateHeight - (lvl * plateHeightDif));
}*/

/*if (event.mouseButton.button == sf::Mouse::Left)
{
    sf::sleep(sf::milliseconds(100));
    while (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        plates[n - 1].setPosition(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
    }
}*/

/*
    plate1.setSize(sf::Vector2f(plateWidth - (lvl * plateWidthDif), 20));
    plate1.setOrigin(plate1.getSize().x / 2 - (plateOriginX + lvl * plateOriginXDif), 0);
    plate1.setPosition(280, plateHeight - (lvl * plateHeightDif));
    plate1.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

    lvl = 1;

    plate2.setSize(sf::Vector2f(plateWidth - (lvl * plateWidthDif), 20));
    plate2.setOrigin(plate1.getSize().x / 2 - (plateOriginX + lvl * plateOriginXDif), 0);
    plate2.setPosition(280, plateHeight - (lvl * plateHeightDif));
    plate2.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

    lvl = 2;

    plate3.setSize(sf::Vector2f(plateWidth - (lvl * plateWidthDif), 20));
    plate3.setOrigin(plate1.getSize().x / 2 - (plateOriginX + lvl * plateOriginXDif), 0);
    plate3.setPosition(280, plateHeight - (lvl * plateHeightDif));
    plate3.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));

    lvl = 10;

    plate4.setSize(sf::Vector2f(plateWidth - (lvl * plateWidthDif), 20));
    plate4.setOrigin(plate1.getSize().x / 2 - (plateOriginX + lvl * plateOriginXDif), 0);
    plate4.setPosition(280, plateHeight - (lvl * plateHeightDif));
    plate4.setFillColor(sf::Color(rand() % 255 + 1, rand() % 255 + 1, rand() % 255 + 1));
*/


//window.draw(plate1);
//window.draw(plate2);
//window.draw(plate3);
//window.draw(plate4);