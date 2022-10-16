#pragma once
#include <cmath>
#include <string>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

enum statList { INTEL, REF, DEX, TECH, COOL, WILL, LUCK, MOVE, BODY, EMP, 
	HEALTH, SERIOUSWOUND, DEATHSAVE, HUMANITY };

enum skillList { CONCENTRATION, CONCEALOBJECT, LIPREADING, PERCEPTION, TRACKING, 
	ATHLETICS, CONTORTIONIST, DANCE, ENDURANCE, RESISTTORTURE, STEALTH, DRIVELAND, 
	PILOTAIR, PILOTSEA, RIDING, ACCOUNTING, ANIMALHANDLING, BUREAUCRACY, BUSINESS, 
	COMPOSITION, CRIMINOLOGY, CRYPTOGRAPHY, DEDUCTION, EDUCATION, GAMBLE, STREETSLANG,
	LIBRARYSEARCH, YOURHOME, TACTICS, WILDERNESSSURVIVAL, BRAWLING, EVASION, MARTIALARTS, 
	MELEEWEAPON, ACTING, PLAYINSTRUMENT, ARCHERY, AUTOFIRE, HANDGUN, HEAVYWEAPON, 
	SHOULDERARMS, BRIBERY, CONVERSATION, HUMANPERCEPTION, INTERROGATION, PERSUASION, 
	PERSONALGROOMING, STREETWISE, TRADING, WARDROBE, AIRVEHICLETECH, BASICTECH, 
	CYBERTECH, DEMOLITIONS, ELECTRONICSSECURITYTECH, FIRSTAID, FORGERY, LANDVEHICLETECH, 
	PAINTDRAWSCULPT, PARAMEDIC, PHOTOGRAPHYFILM, PICKLOCK, PICKPOCKET, SEAVEHICLETECH, 
	WEAPONSTECH, SCIENCE};

struct character
{
	string handle;
	string role;
	string roleAbility;
	int roleRank = 0;
	int stats[14];
	int skills[66];
};

string nameGenerator();
void skillsGenerator(int storage[], int skillDouble = 0);
void edgerunnerStatGenerator(int statBlock[][10], int stats[]);
void determineGenerator(string classInput, character& storage);
void outputCharacter(ifstream& input, ofstream& output, character storage);

void arraySet(int skills[]);
statList statConvert(string input);
skillList skillConvert(string input);

void rockerboyEdgerunner(character& storage);
void soloEdgerunner(character& storage);
void netrunnerEdgerunner(character& storage);
void techEdgerunner(character& storage);
void medTechEdgerunner(character& storage);
void mediaEdgerunner(character& storage);
void execEdgerunner(character& storage);
void lawmenEdgerunner(character& storage);
void fixerEdgerunner(character& storage);
void nomadEdgerunner(character& storage);

void rockerboyComplete(character& storage);
void soloComplete(character& storage);
void netrunnerComplete(character& storage);
void techComplete(character& storage);
void medTechComplete(character& storage);
void mediaComplete(character& storage);
void execComplete(character& storage);
void lawmenComplete(character& storage);
void fixerComplete(character& storage);
void nomadComplete(character& storage);