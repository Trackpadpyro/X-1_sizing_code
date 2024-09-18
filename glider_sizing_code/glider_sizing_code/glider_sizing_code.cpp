#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h> 
#include <time.h>

#include <SFML/Graphics.hpp>
#include "window setup.h"

using namespace std;

int main()
{
	//-------------; setup space
	sf::Font font;
	if (!font.loadFromFile("arial.ttf"))
	{cout << "failed to load font" << endl; exit(1);}
	sf::Text text;
	int font_title_scale = 32;
	string title;
	text.setFont(font);
	double display_table[fineness][fineness * rat];
	
	//seed random time
	srand(time(NULL));

	cout << "Ground distance: " << drop_height / tan(glide_angle) << " (m), Flight time: " << drop_height / sin(glide_angle) / drop_speed << " (s)" << endl;
	for (int i = 0; i < fineness; i++) {
		for (int j = 0; j < fineness * rat; j++) {
			g_array[i][j].set(
				0.19 + (i + 1) * (wingspan_limit - 0.19) / fineness,
				0.05 * (j + 1) / (fineness * rat) + 0.02
			);
		}
	}
	//-------------

	while (window.isOpen())
	{
		//-------------; 

		//-------------

		//clear window
		window.clear();
		//get mouse position
		pixelPos = sf::Mouse::getPosition(window);
		//user input
		while (window.pollEvent(event))
		{
			check_input();
		}

		//-------------; drawing space
		switch (counter % 9) {
		case 0:
			title = "Aspect ratio";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].a();
				}
			}
			break;
		case 1:
			title = "Wing area (m\^2)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].s();
				}
			}
			break;
		case 2:
			title = "Cl";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].cl();
				}
			}
			break;
		case 3:
			title = "Cd";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].cd();
				}
			}
			break;
		case 4:
			title = "Weight (N)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].weight();
				}
			}
			break;
		case 5:
			title = "Mass (kg)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].mass();
				}
			}
			break;
		case 6:
			title = "Span (m)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].span;
				}
			}
			break;
		case 7:
			title = "Chord (m)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].chord;
				}
			}
			break;
		case 8:
			title = "Predicted mass (g)";
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = (g_array[i][j].pred_mass() + electronics_mass) * 1000;
				}
			}
			break;
		default:
			break;
		}
		text.setString(title);
		text.setStyle(sf::Text::Bold);
		text.setPosition(sf::Vector2f(x_size / 2 - title.length() / 4 * font_title_scale, 0));
		text.setCharacterSize(font_title_scale);
		text.setFillColor(sf::Color::White);
		window.draw(text);

		text.setCharacterSize(font_title_scale / 2);

		for (int i = 0; i < fineness; i++) {
			for (int j = 0; j < fineness * rat; j++) {
				if (display_table[i][j] == display_table[i][j]) {
					text.setString(to_string(display_table[i][j]));
				}
				else {
					text.setString("DNE");
				}
				text.setStyle(sf::Text::Bold);
				text.setPosition(sf::Vector2f(margin + i * spacing_x, margin + j * spacing_y));
				if (g_array[i][j].check_all()) {
					text.setFillColor(sf::Color::White);
				}
				else {
					text.setFillColor(sf::Color::Red);
				}
				window.draw(text);
			}
		}
		//-------------
		window.display();
	}

	ofstream rec;
	for (int k = 0; k < 9; k++) {
		switch (k % 9) {
		case 0:
			rec.open("Aspect ratio.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].a();
				}
			}
			break;
		case 1:
			rec.open("Wing area.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].s();
				}
			}
			break;
		case 2:
			rec.open("Cl.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].cl();
				}
			}
			break;
		case 3:
			rec.open("Cd.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].cd();
				}
			}
			break;
		case 4:
			rec.open("Weight.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].weight();
				}
			}
			break;
		case 5:
			rec.open("Mass.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].mass();
				}
			}
			break;
		case 6:
			rec.open("Span.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].span;
				}
			}
			break;
		case 7:
			rec.open("Chord.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = g_array[i][j].chord;
				}
			}
			break;
		case 8:
			rec.open("Predicted mass.txt");
			for (int i = 0; i < fineness; i++) {
				for (int j = 0; j < fineness * rat; j++) {
					display_table[i][j] = (g_array[i][j].pred_mass() + electronics_mass) * 1000;
				}
			}
			break;
		default:
			break;
		}

		for (int i = 0; i < fineness; i++) {
			for (int j = 0; j < fineness * rat; j++) {
				rec << display_table[i][j];
				if (j == fineness * rat - 1) {
					rec << endl;
				}
				else {
					rec << ", ";
				}
			}
		}
		rec.close();
	}
	/*

	*/
}
