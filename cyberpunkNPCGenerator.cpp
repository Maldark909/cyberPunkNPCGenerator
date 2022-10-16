#include "netrunner.h"

int main()
{
	ifstream input;
	ofstream output;
	character storage;
	string stringInput;
	char handleInput[50];

	srand(int(time(NULL)));

	input.open("cyberpunkNPCGeneratorTemplate.txt");
	if (!input.is_open())
	{
		cout << "Template not found! Please use a known Cyberpunk Red Template!" << endl;
		return -1;
	}

	cout << "Please give the NPC a handle (--random for a random handle)" << endl; //NOTE FOR FUTURE SELF: ADD RANDOM NAME GENERATOR
	cin.get(handleInput, 50);
	if (strcmp(handleInput, "--random") == 0)
		storage.handle = nameGenerator();
	else
		storage.handle = handleInput;
	output.open(storage.handle + ".txt");
	if (!output.is_open())
	{
		cout << "Unable to open output character sheet! Please restart using a different handle...." << endl;
		return -1;
	}

	cout << "Please input what role the NPC is:" << endl;
	cout << "-Rockerboy, -Solo, -Netrunner, -Tech, -Medtech, -Media, -Exec, -Lawmen, -Fixer, -Nomad" << endl;
	cin >> stringInput;

	if (!(stringInput == "-Rockerboy" || stringInput == "-Solo" || stringInput == "-Netrunner" ||
		stringInput == "-Tech" || stringInput == "-Medtech" || stringInput == "-Media" ||
		stringInput == "-Exec" || stringInput == "-Lawmen" || stringInput == "-Fixer" ||
		stringInput == "-Nomad"))
	{
		cout << "Please use the correct phrasing for input!" << endl;
		return -1;
	}
	
	//SET ARRAY TO 0
	arraySet(storage.skills);

	//DETERMINE GENERATOR
	determineGenerator(stringInput, storage);

	//OUTPUT RESULTS
	outputCharacter(input, output, storage);

	return 0;
}

string nameGenerator()
{
	ifstream firstInput;
	ifstream secondInput;
	ifstream thirdInput;
	int nameCount = (rand() % 3) + 1;
	int loopFind1, loopFind2, loopFind3;
	int i = 0;
	string result = "random";
	string first, last, nick;

	firstInput.open("firstName.txt");
	secondInput.open("lastName.txt");
	thirdInput.open("nickName.txt");

	loopFind1 = (rand() % 20) + 2;
	loopFind2 = (rand() % 20) + 2;
	loopFind3 = (rand() % 20) + 2;

	while (i < loopFind1)
	{
		first.clear();
		getline(firstInput, first);
		i = i + 1;
	}
	i = 0;
	while (i < loopFind2)
	{
		last.clear();
		getline(secondInput, last);
		i = i + 1;
	}
	i = 0;
	while (i < loopFind3)
	{
		nick.clear();
		getline(thirdInput, nick);
		i = i + 1;
	}

	if(nameCount == 1)
		return nick;

	if (nameCount == 2)
	{
		result.clear();
		result = first + ' ' + last;
	}

	if (nameCount == 3)
	{
		result.clear();
		result = first + " \"" + nick + "\" " + last;
	}

	return result;
}

void arraySet(int skills[])
{
	int i = 0;
	while (i < 66)
	{
		skills[i] = 0;
		i = i + 1;
	}
	return;
}

void edgerunnerStatGenerator(int statBlock[][10], int stats[])
{
	int i = 0;

	cout << endl << endl << "Generating Stats..." << endl;
	while (i < 10)
	{
		stats[i] = statBlock[rand() % 10][i];
		i = i + 1;
	}
	stats[HEALTH] = int(10 + (ceil((stats[BODY] + stats[WILL]) / 2) * 5));
	stats[SERIOUSWOUND] = int(ceil(stats[HEALTH] / 2));
	stats[DEATHSAVE] = stats[BODY];
	stats[HUMANITY] = stats[EMP] * 10;
}

void skillsGenerator(int storage[], int skillDouble)
{
	int i = 40;
	int slot = 0;

	cout << endl << endl << "Generating Skills..." << endl;
	while (i < 86)
	{
		slot = rand() % 20;
		if (storage[slot] < 6)
		{
			if (slot < skillDouble)
			{
				storage[slot] = storage[slot] + 2;
				i = i + 2;
			}
			if (slot >= skillDouble)
			{
				storage[slot] = storage[slot] + 1;
				i = i + 1;
			}
		}
	}

	return;
}

void determineGenerator(string classInput, character& storage)
{
	if (classInput == "-Rockerboy")
		rockerboyEdgerunner(storage);
	if (classInput == "-Solo")
		soloEdgerunner(storage);
	if (classInput == "-Netrunner")
		netrunnerEdgerunner(storage);
	if (classInput == "-Tech")
		techEdgerunner(storage);
	if (classInput == "-Medtech")
		medTechEdgerunner(storage);
	if (classInput == "-Media")
		mediaEdgerunner(storage);
	if (classInput == "-Exec")
		execEdgerunner(storage);
	if (classInput == "-Lawmen")
		lawmenEdgerunner(storage);
	if (classInput == "-Fixer")
		fixerEdgerunner(storage);
	if (classInput == "-Nomad")
		nomadEdgerunner(storage);

	return;
}

void outputCharacter(ifstream& input, ofstream& output, character storage)
{
	string lineBuffer;
	string outputBuffer;
	statList statBuffer;
	skillList skillBuffer;
	bool noHit = false;
	while (!input.eof())
	{
		noHit = true;
		getline(input, lineBuffer);
		if (lineBuffer.find("??") != string::npos)
		{
			noHit = false;
			if (lineBuffer.substr(lineBuffer.find("??") + 2, lineBuffer.length() - 1) == "HANDLE")
				outputBuffer = lineBuffer.substr(0, lineBuffer.find("??")) + storage.handle;
			if (lineBuffer.substr(lineBuffer.find("??") + 2, lineBuffer.length() - 1) == "ROLE")
				outputBuffer = lineBuffer.substr(0, lineBuffer.find("??")) + storage.role;
			if (lineBuffer.substr(lineBuffer.find("??") + 2, lineBuffer.length() - 1) == "ROLEABILITY")
				outputBuffer = lineBuffer.substr(0, lineBuffer.find("??")) + storage.roleAbility;
			if (lineBuffer.substr(lineBuffer.find("??") + 2, lineBuffer.length() - 1) == "ROLERANK")
				outputBuffer = lineBuffer.substr(0, lineBuffer.find("??")) + to_string(storage.roleRank);
		}
		if (lineBuffer.find(">>") != string::npos)
		{
			noHit = false;
			statBuffer = statConvert(lineBuffer.substr(lineBuffer.find(">>") + 2, lineBuffer.length() - 1));
			outputBuffer = lineBuffer.substr(0, lineBuffer.find(">>")) + to_string(storage.stats[statBuffer]);
		}
		if (lineBuffer.find("###") != string::npos)
		{
			noHit = false;
			skillBuffer = skillConvert(lineBuffer.substr(lineBuffer.find("###") + 3, lineBuffer.length() - 1));
			outputBuffer = lineBuffer.substr(0, lineBuffer.find("###")) + to_string(storage.skills[skillBuffer]);
		}
		if (noHit)
			outputBuffer = lineBuffer;

		cout << outputBuffer << endl;
		output << outputBuffer << endl;
	}

	return;
}

statList statConvert(string input)
{
	if (input == "INTEL")
		return INTEL;
	if (input == "REF")
		return REF;
	if (input == "DEX")
		return DEX;
	if (input == "TECH")
		return TECH;
	if (input == "COOL")
		return COOL;
	if (input == "WILL")
		return WILL;
	if (input == "LUCK")
		return LUCK;
	if (input == "MOVE")
		return MOVE;
	if (input == "BODY")
		return BODY;
	if (input == "EMP")
		return EMP;
	if (input == "HEALTH")
		return HEALTH;
	if (input == "SERIOUSWOUND")
		return SERIOUSWOUND;
	if (input == "DEATHSAVE")
		return DEATHSAVE;
	if (input == "HUMANITY")
		return HUMANITY;

	return INTEL;
}

skillList skillConvert(string input)
{
	if (input == "CONCENTRATION")
		return CONCENTRATION;
	if (input == "CONCEALOBJECT")
		return CONCEALOBJECT;
	if (input == "LIPREADING")
		return LIPREADING;
	if (input == "PERCEPTION")
		return PERCEPTION;
	if (input == "TRACKING")
		return TRACKING;
	if (input == "ATHLETICS")
		return ATHLETICS;
	if (input == "CONTORTIONIST")
		return CONTORTIONIST;
	if (input == "DANCE")
		return DANCE;
	if (input == "ENDURANCE")
		return ENDURANCE;
	if (input == "RESISTTORTURE")
		return RESISTTORTURE;
	if (input == "STEALTH")
		return STEALTH;
	if (input == "DRIVELAND")
		return DRIVELAND;
	if (input == "PILOTAIR")
		return PILOTAIR;
	if (input == "PILOTSEA")
		return PILOTSEA;
	if (input == "RIDING")
		return RIDING;
	if (input == "ACCOUNTING")
		return ACCOUNTING;
	if (input == "ANIMALHANDLING")
		return ANIMALHANDLING;
	if (input == "BUREAUCRACY")
		return BUREAUCRACY;
	if (input == "BUSINESS")
		return BUSINESS;
	if (input == "COMPOSITION")
		return COMPOSITION;
	if (input == "CRIMINOLOGY")
		return CRIMINOLOGY;
	if (input == "CRYPTOGRAPHY")
		return CRYPTOGRAPHY;
	if (input == "DEDUCTION")
		return DEDUCTION;
	if (input == "EDUCATION")
		return EDUCATION;
	if (input == "GAMBLE")
		return GAMBLE;
	if (input == "STREETSLANG")
		return STREETSLANG;
	if (input == "LIBRARYSEARCH")
		return LIBRARYSEARCH;
	if (input == "YOURHOME")
		return YOURHOME;
	if (input == "TACTICS")
		return TACTICS;
	if (input == "WILDERNESSSURVIVAL")
		return WILDERNESSSURVIVAL;
	if (input == "BRAWLING")
		return BRAWLING;
	if (input == "EVASION")
		return EVASION;
	if (input == "MARTIALARTS")
		return MARTIALARTS;
	if (input == "MELEEWEAPON")
		return MELEEWEAPON;
	if (input == "ACTING")
		return ACTING;
	if (input == "PLAYINSTRUMENT")
		return PLAYINSTRUMENT;
	if (input == "ARCHERY")
		return ARCHERY;
	if (input == "AUTOFIRE")
		return AUTOFIRE;
	if (input == "HANDGUN")
		return HANDGUN;
	if (input == "HEAVYWEAPON")
		return HEAVYWEAPON;
	if (input == "SHOULDERARMS")
		return SHOULDERARMS;
	if (input == "BRIBERY")
		return BRIBERY;
	if (input == "CONVERSATION")
		return CONVERSATION;
	if (input == "HUMANPERCEPTION")
		return HUMANPERCEPTION;
	if (input == "INTERROGATION")
		return INTERROGATION;
	if (input == "PERSUASION")
		return PERSUASION;
	if (input == "PERSONALGROOMING")
		return PERSONALGROOMING;
	if (input == "STREETWISE")
		return STREETWISE;
	if (input == "TRADING")
		return TRADING;
	if (input == "WARDROBE")
		return WARDROBE;
	if (input == "AIRVEHICLETECH")
		return AIRVEHICLETECH;
	if (input == "BASICTECH")
		return BASICTECH;
	if (input == "CYBERTECH")
		return CYBERTECH;
	if (input == "DEMOLITIONS")
		return DEMOLITIONS;
	if (input == "ELECTRONICSSECURITYTECH")
		return ELECTRONICSSECURITYTECH;
	if (input == "FIRSTAID")
		return FIRSTAID;
	if (input == "FORGERY")
		return FORGERY;
	if (input == "LANDVEHICLETECH")
		return LANDVEHICLETECH;
	if (input == "PAINTDRAWSCULPT")
		return PAINTDRAWSCULPT;
	if (input == "PARAMEDIC")
		return PARAMEDIC;
	if (input == "PHOTOGRAPHYFILM")
		return PHOTOGRAPHYFILM;
	if (input == "PICKLOCK")
		return PICKLOCK;
	if (input == "PICKPOCKET")
		return PICKPOCKET;
	if (input == "SEAVEHICLETECH")
		return SEAVEHICLETECH;
	if (input == "WEAPONSTECH")
		return WEAPONSTECH;
	if (input == "SCIENCE")
		return SCIENCE;

	return CONCENTRATION;
}

void rockerboyEdgerunner(character& storage)
{
	int statBlock[10][10] = {
		7, 6, 6, 5, 6, 8, 7, 7, 3, 8,
		3, 7, 7, 7, 7, 6, 7, 7, 5, 8,
		4, 5, 7, 7, 6, 6, 7, 7, 5, 8,
		4, 5, 7, 7, 6, 8, 7, 6, 3, 8,
		3, 7, 7, 7, 6, 8, 6, 5, 4, 7,
		5, 6, 7, 5, 7, 8, 5, 7, 3, 7,
		5, 6, 6, 7, 7, 8, 7, 6, 3, 6,
		5, 7, 7, 5, 6, 6, 6, 6, 4, 8,
		3, 5, 5, 6, 7, 8, 7, 5, 5, 7,
		4, 5, 6, 5, 8, 8, 7, 6, 4, 7 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Rockerboy";
	storage.roleAbility = "Charismatic Impact";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[COMPOSITION] = skills[13];
	storage.skills[HANDGUN] = skills[14];
	storage.skills[MELEEWEAPON] = skills[15];
	storage.skills[PERSONALGROOMING] = skills[16];
	storage.skills[PLAYINSTRUMENT] = skills[17];
	storage.skills[STREETWISE] = skills[18];
	storage.skills[WARDROBE] = skills[19];

	return;
}

void soloEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		6, 7, 7, 3, 8, 6, 5, 5, 6, 5,
		7, 8, 6, 3, 6, 6, 7, 5, 6, 6,
		5, 8, 7, 4, 7, 7, 6, 7, 8, 5,
		5, 8, 6, 4, 6, 7, 6, 5, 7, 6,
		6, 6, 7, 5, 7, 6, 7, 6, 8, 4,
		7, 7, 6, 5, 7, 6, 6, 7, 7, 5,
		7, 7, 6, 5, 6, 7, 7, 6, 6, 6,
		7, 8, 7, 5, 6, 6, 5, 6, 8, 4,
		7, 7, 6, 4, 6, 6, 6, 5, 6, 5,
		6, 6, 8, 5, 6, 6, 5, 6, 6, 5 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Solo";
	storage.roleAbility = "Combat Awareness";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills, 1);
	storage.skills[ATHLETICS] = skills[1];
	storage.skills[BRAWLING] = skills[2];
	storage.skills[CONCENTRATION] = skills[3];
	storage.skills[CONVERSATION] = skills[4];
	storage.skills[EDUCATION] = skills[5];
	storage.skills[EVASION] = skills[6];
	storage.skills[FIRSTAID] = skills[7];
	storage.skills[HUMANPERCEPTION] = skills[8];
	storage.skills[STREETSLANG] = skills[9];
	storage.skills[YOURHOME] = skills[10];
	storage.skills[PERCEPTION] = skills[11];
	storage.skills[PERSUASION] = skills[12];
	storage.skills[STEALTH] = skills[13];
	storage.skills[AUTOFIRE] = skills[0];
	storage.skills[HANDGUN] = skills[14];
	storage.skills[INTERROGATION] = skills[15];
	storage.skills[MELEEWEAPON] = skills[16];
	storage.skills[RESISTTORTURE] = skills[17];
	storage.skills[SHOULDERARMS] = skills[18];
	storage.skills[TACTICS] = skills[19];

	return;
}

void netrunnerEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		5, 8, 7, 7, 7, 4, 8, 7, 7, 4,
		5, 6, 7, 5, 8, 3, 8, 7, 5, 5,
		5, 6, 8, 6, 6, 4, 7, 6, 7, 4,
		5, 7, 7, 7, 7, 5, 8, 6, 5, 5,
		5, 8, 8, 5, 7, 3, 7, 5, 5, 6,
		6, 6, 6, 7, 8, 4, 7, 7, 6, 6,
		6, 6, 6, 7, 6, 5, 7, 7, 7, 6,
		5, 7, 8, 6, 8, 4, 8, 5, 7, 4,
		7, 6, 7, 7, 6, 3, 6, 5, 6, 5,
		7, 8, 6, 6, 6, 4, 7, 7, 5, 6 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Netrunner";
	storage.roleAbility = "Interface";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills, 1);
	storage.skills[ATHLETICS] = skills[1];
	storage.skills[BRAWLING] = skills[2];
	storage.skills[CONCENTRATION] = skills[3];
	storage.skills[CONVERSATION] = skills[4];
	storage.skills[EDUCATION] = skills[5];
	storage.skills[EVASION] = skills[6];
	storage.skills[FIRSTAID] = skills[7];
	storage.skills[HUMANPERCEPTION] = skills[8];
	storage.skills[STREETSLANG] = skills[9];
	storage.skills[YOURHOME] = skills[10];
	storage.skills[PERCEPTION] = skills[11];
	storage.skills[PERSUASION] = skills[12];
	storage.skills[STEALTH] = skills[13];
	storage.skills[BASICTECH] = skills[14];
	storage.skills[CONCEALOBJECT] = skills[15];
	storage.skills[CRYPTOGRAPHY] = skills[16];
	storage.skills[CYBERTECH] = skills[17];
	storage.skills[ELECTRONICSSECURITYTECH] = skills[0];
	storage.skills[HANDGUN] = skills[18];
	storage.skills[LIBRARYSEARCH] = skills[19];

	return;
}

void techEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		6, 7, 7, 8, 4, 4, 5, 5, 7, 6,
		7, 6, 6, 7, 5, 3, 7, 7, 5, 5,
		8, 6, 5, 7, 5, 4, 7, 7, 5, 7,
		7, 8, 7, 8, 4, 4, 6, 5, 6, 7,
		6, 6, 7, 6, 4, 3, 7, 7, 6, 6,
		8, 7, 5, 6, 3, 3, 7, 6, 6, 7,
		8, 6, 7, 8, 4, 4, 7, 6, 7, 6,
		8, 8, 7, 8, 5, 4, 6, 5, 6, 6,
		6, 6, 7, 8, 3, 3, 5, 7, 7, 7,
		8, 8, 5, 6, 4, 4, 6, 5, 6, 6 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Tech";
	storage.roleAbility = "Maker";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills, 1);
	storage.skills[ATHLETICS] = skills[1];
	storage.skills[BRAWLING] = skills[2];
	storage.skills[CONCENTRATION] = skills[3];
	storage.skills[CONVERSATION] = skills[4];
	storage.skills[EDUCATION] = skills[5];
	storage.skills[EVASION] = skills[6];
	storage.skills[FIRSTAID] = skills[7];
	storage.skills[HUMANPERCEPTION] = skills[8];
	storage.skills[STREETSLANG] = skills[9];
	storage.skills[YOURHOME] = skills[10];
	storage.skills[PERCEPTION] = skills[11];
	storage.skills[PERSUASION] = skills[12];
	storage.skills[STEALTH] = skills[13];
	storage.skills[BASICTECH] = skills[14];
	storage.skills[CYBERTECH] = skills[15];
	storage.skills[ELECTRONICSSECURITYTECH] = skills[0];
	storage.skills[LANDVEHICLETECH] = skills[16];
	storage.skills[SHOULDERARMS] = skills[17];
	storage.skills[SCIENCE] = skills[18];
	storage.skills[WEAPONSTECH] = skills[19];

	return;
}

void medTechEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		7, 5, 6, 7, 5, 3, 8, 5, 5, 7,
		6, 7, 7, 7, 4, 4, 6, 7, 7, 7,
		6, 5, 5, 8, 5, 3, 8, 5, 7, 8,
		8, 7, 6, 8, 3, 5, 6, 6, 5, 7,
		6, 7, 5, 7, 5, 5, 8, 7, 6, 8,
		8, 5, 5, 8, 5, 5, 6, 6, 5, 6,
		8, 6, 5, 8, 5, 4, 8, 5, 7, 7,
		6, 5, 7, 7, 3, 5, 8, 5, 5, 8,
		6, 6, 7, 7, 5, 4, 6, 6, 5, 6,
		8, 7, 6, 6, 3, 4, 8, 7, 6, 7 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Medtech";
	storage.roleAbility = "Medicine";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills, 1);
	storage.skills[ATHLETICS] = skills[1];
	storage.skills[BRAWLING] = skills[2];
	storage.skills[CONCENTRATION] = skills[3];
	storage.skills[CONVERSATION] = skills[4];
	storage.skills[EDUCATION] = skills[5];
	storage.skills[EVASION] = skills[6];
	storage.skills[FIRSTAID] = skills[7];
	storage.skills[HUMANPERCEPTION] = skills[8];
	storage.skills[STREETSLANG] = skills[9];
	storage.skills[YOURHOME] = skills[10];
	storage.skills[PERCEPTION] = skills[11];
	storage.skills[PERSUASION] = skills[12];
	storage.skills[STEALTH] = skills[13];
	storage.skills[BASICTECH] = skills[14];
	storage.skills[CYBERTECH] = skills[15];
	storage.skills[DEDUCTION] = skills[16];
	storage.skills[PARAMEDIC] = skills[0];
	storage.skills[RESISTTORTURE] = skills[17];
	storage.skills[SCIENCE] = skills[18];
	storage.skills[SHOULDERARMS] = skills[19];

	return;
}

void mediaEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		6, 6, 5, 5, 8, 7, 5, 7, 5, 7,
		8, 7, 7, 3, 6, 6, 6, 5, 6, 8,
		6, 7, 7, 5, 6, 8, 5, 5, 5, 7,
		6, 5, 7, 5, 6, 7, 5, 5, 6, 6,
		6, 6, 7, 4, 8, 7, 6, 7, 5, 8,
		8, 5, 6, 3, 7, 6, 6, 5, 6, 7,
		6, 5 ,6, 5, 6, 8, 6, 6, 7, 8,
		7, 7, 5, 4, 6, 7, 6, 5, 6, 7,
		7, 6, 6, 3, 7, 6, 7, 6, 7, 6 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Media";
	storage.roleAbility = "Credibility";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[BRIBERY] = skills[13];
	storage.skills[COMPOSITION] = skills[14];
	storage.skills[DEDUCTION] = skills[15];
	storage.skills[HANDGUN] = skills[16];
	storage.skills[LIBRARYSEARCH] = skills[17];
	storage.skills[LIPREADING] = skills[18];
	storage.skills[PHOTOGRAPHYFILM] = skills[19];

	return;
}

void execEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		8, 5, 5, 3, 8, 6, 6, 5, 5, 7,
		8, 6, 6, 4, 7, 6, 7, 7, 5, 7,
		8, 7, 6, 3, 8, 6, 7, 6, 4, 5,
		8, 5, 7, 5, 6, 5, 6, 5, 5, 7,
		7, 7, 6, 5, 8, 5, 7, 7, 5, 6,
		5, 7, 7, 3, 6, 7, 6, 5, 5, 7,
		6, 6, 7, 5, 8, 7, 6, 7, 4, 6,
		6, 7, 7, 3, 7, 5, 7, 5, 5, 7,
		7, 6, 7, 5, 7, 5, 7, 6, 5, 5,
		7, 7, 5, 5, 8, 6, 6, 7, 4, 7 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Exec";
	storage.roleAbility = "Teamwork";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[ACCOUNTING] = skills[13];
	storage.skills[BUREAUCRACY] = skills[14];
	storage.skills[BUSINESS] = skills[15];
	storage.skills[DEDUCTION] = skills[16];
	storage.skills[HANDGUN] = skills[17];
	storage.skills[LIPREADING] = skills[18];
	storage.skills[PERSONALGROOMING] = skills[19];

	return;
}

void lawmenEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		5, 6, 7, 5, 7, 8, 5, 6, 5, 6,
		6, 6, 6, 5, 6, 8, 5, 7, 5, 5,
		5, 7, 7, 7, 6, 7, 5, 5, 7, 6,
		6, 6, 7, 6, 6, 8, 5, 7, 7, 6,
		6, 6, 7, 6, 7, 7, 6, 5, 5, 6,
		7, 6, 5, 5, 7, 8, 5, 6, 7, 4,
		7, 8, 7, 5, 6, 8, 7, 6, 5, 4,
		5, 6, 6, 5, 6, 8, 5, 7, 6, 4,
		7, 7, 5, 5, 7, 7, 6, 5, 5, 6,
		6, 6, 5, 6, 8, 7, 5, 7, 6, 6 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Lawman";
	storage.roleAbility = "Backup";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[AUTOFIRE] = skills[13];
	storage.skills[CRIMINOLOGY] = skills[14];
	storage.skills[DEDUCTION] = skills[15];
	storage.skills[HANDGUN] = skills[16];
	storage.skills[INTERROGATION] = skills[17];
	storage.skills[SHOULDERARMS] = skills[18];
	storage.skills[TRACKING] = skills[19];

	return;
}

void fixerEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		8, 5, 7, 4, 6, 5, 8, 5, 5, 8,
		8, 5, 5, 5, 6, 7, 8, 7 ,5, 7,
		6, 6, 6, 4, 5, 6, 8, 6, 3, 8,
		7, 7, 5, 5, 7, 6, 7, 7, 5, 8,
		8, 6, 6, 3, 6, 5, 8, 7, 5, 6,
		8, 7, 5, 5, 6, 7, 7, 5, 3, 6,
		8, 6, 6, 5, 6, 5, 6, 7, 5, 8,
		6, 6, 7, 4, 7, 6, 7, 7, 4, 7,
		8, 7, 7, 5, 5, 5, 7, 6, 5, 7,
		6, 5, 6, 5, 5, 6, 8, 6, 4, 7 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Fixer";
	storage.roleAbility = "Operator";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[BRIBERY] = skills[13];
	storage.skills[BUSINESS] = skills[14];
	storage.skills[FORGERY] = skills[15];
	storage.skills[HANDGUN] = skills[16];
	storage.skills[PICKLOCK] = skills[17];
	storage.skills[STREETWISE] = skills[18];
	storage.skills[TRADING] = skills[19];

	return;
}

void nomadEdgerunner(character& storage)
{
	string input;
	int statBlock[10][10] = {
		6, 6, 8, 3, 6, 7, 6, 6, 6, 4,
		5, 7, 6, 5, 8, 8, 8, 7, 5, 4,
		5, 8, 6, 3, 8, 7, 6, 5, 6, 5,
		5, 8, 7, 4, 8, 6, 7, 7, 7, 5,
		6, 6, 6, 3, 6, 7, 6, 7, 7, 4,
		7, 6, 8, 4, 6, 7, 6, 5, 6, 5,
		6, 7, 8, 4, 6, 6, 7, 5, 7, 5,
		5, 7, 8, 1, 8, 6, 7, 5, 5, 5,
		6, 7, 6, 4, 8, 6, 6, 6, 6, 6,
		5, 6, 7, 4, 7, 8, 7, 7, 7, 4 };
	int skills[20] = { 2, 2, 2, 2, 2, 2, 2,
		2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,
		2 };

	//ROLE INPUT
	storage.role = "Nomad";
	storage.roleAbility = "Moto";

	//STATS GENERATION
	edgerunnerStatGenerator(statBlock, storage.stats);

	//SKILLS GENERATION
	skillsGenerator(skills);
	storage.skills[ATHLETICS] = skills[0];
	storage.skills[BRAWLING] = skills[1];
	storage.skills[CONCENTRATION] = skills[2];
	storage.skills[CONVERSATION] = skills[3];
	storage.skills[EDUCATION] = skills[4];
	storage.skills[EVASION] = skills[5];
	storage.skills[FIRSTAID] = skills[6];
	storage.skills[HUMANPERCEPTION] = skills[7];
	storage.skills[STREETSLANG] = skills[8];
	storage.skills[YOURHOME] = skills[9];
	storage.skills[PERCEPTION] = skills[10];
	storage.skills[PERSUASION] = skills[11];
	storage.skills[STEALTH] = skills[12];
	storage.skills[ANIMALHANDLING] = skills[13];
	storage.skills[DRIVELAND] = skills[14];
	storage.skills[HANDGUN] = skills[15];
	storage.skills[MELEEWEAPON] = skills[16];
	storage.skills[TRACKING] = skills[17];
	storage.skills[TRADING] = skills[18];
	storage.skills[WILDERNESSSURVIVAL] = skills[19];

	return;
}