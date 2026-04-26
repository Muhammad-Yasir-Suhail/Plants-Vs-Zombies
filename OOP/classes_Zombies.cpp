#include "classes_Zombies.h"
#include "classes_Plants.h"
#include "SFML/Graphics.hpp"
#include <iostream>

using namespace std;

void Zombie::update(RenderWindow& window) {

	if (state == "wait") {
		timer+= 0.23;

		if (timer > spawnTime) {
			state = "move";
			timer = 0;
			return;
		}
	}
	
	// prints zombie on the window
	if (state == "move") {
		timer++;

		//checks slow
		if (slow >= 0) {
			timer -= 0.5;
			slow -= 1;
		}
		
		posx = (timer - spawnTime) * -2 + 1000 - 90;

		if (posx > pixelx)
			return;

	}
	animate(window);
	
	//draw zombie
	texture.loadFromFile(imageFile);
	zombieSprite.setTexture(texture);
	zombieSprite.setPosition(posx, posy);
	window.draw(zombieSprite);
}

void Zombie::animate(RenderWindow& window) {
	int current;

	check += 0.5;

	if (state == "wait") {
		return;
	}

	if (state == "killed") {

		current = (int)check % 20;

		imageFile = "assets/Zombies/NormalZombie/BoomDie/BoomDie_" + to_string(current);
		imageFile += ".png";

	}

	else if (health > 80) {

		head = 0;

		if (state == "move") {

			current = (int)check % 22;

			imageFile = "assets/Zombies/NormalZombie/Zombie/Zombie_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % 21;

			imageFile = "assets/Zombies/NormalZombie/ZombieAttack/ZombieAttack_" + to_string(current);
			imageFile += ".png";
		}

	}

	//lost cone
	else {

		if (head < 12) {

			head += 0.46;
			current = (head);

			imageFile = "assets/Zombies/NormalZombie/ZombieHead/ZombieHead_" + to_string(current);
			imageFile += ".png";

			texture.loadFromFile(imageFile);
			zombieSprite.setTexture(texture);
			zombieSprite.setPosition(posx + 50, posy);
			window.draw(zombieSprite);

		}

		if (state == "move") {

			current = (int)check % (18);

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHead/ZombieLostHead_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % (11);

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHeadAttack/ZombieLostHeadAttack_" + to_string(current);
			imageFile += ".png";
		}
		else {

			current = (int)check % (10);

			if (check > 5)
				death();

			imageFile = "assets/Zombies/NormalZombie/ZombieDie/ZombieDie_" + to_string(current);
			imageFile += ".png";


		}
	}


}


bool Zombie::hitBullet(int damage) {

	health -= damage;

	if (health <= 0) {

		state = "died";
		check = 0;
		return true;
	}
	else 
		return false;
}

bool Zombie::collisionZombie(int otherxStart, int otherxEnd, int otheryStart, int otheryEnd) {

	if (posx < otherxEnd && (posx + endx) > otherxStart && posy < otheryEnd && (posy + endy) > otheryStart) {

		return true;
	}
	return false;
}

string Zombie::checkState() { return state; }

void Zombie::killed() {
		state = "killed";
		check = 0;
}

bool Zombie:: checkKilled() {
	if ((check > 57 && state == "killed")|| state == "death")
		return true;
	return false;
}

void SimpleZombie::animate(RenderWindow& window) {
	int current;

	check += 0.5;

	if (state == "wait") {
		return;
	}

	if (state == "killed") {

		current = (int)check % 20;

		imageFile = "assets/Zombies/NormalZombie/BoomDie/BoomDie_" + to_string(current);
		imageFile += ".png";
		
	}

	else if (health > 80) {

		head = 0;

		if (state == "move") {

			current = (int)check % 22;

			imageFile = "assets/Zombies/NormalZombie/Zombie/Zombie_" + to_string(current);
			imageFile += ".png";
		}
		else if(state == "stop") {
			current = (int)check % 21;

			imageFile = "assets/Zombies/NormalZombie/ZombieAttack/ZombieAttack_" + to_string(current);
			imageFile += ".png";
		}

	}
	else {

		if (head < 12) {

			head+= 0.46;
			current = (head);

			imageFile = "assets/Zombies/NormalZombie/ZombieHead/ZombieHead_" + to_string(current);
			imageFile += ".png";

			texture.loadFromFile(imageFile);
			zombieSprite.setTexture(texture);
			zombieSprite.setPosition(posx + 50, posy );
			window.draw(zombieSprite);

		}

		if (state == "move") {

			current = (int)check % (18);

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHead/ZombieLostHead_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % (11 );

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHeadAttack/ZombieLostHeadAttack_" + to_string(current);
			imageFile += ".png";
		}
		else {

			current = (int)check % (10);

			if (check > 5 )
				death();

			imageFile = "assets/Zombies/NormalZombie/ZombieDie/ZombieDie_" + to_string(current);
			imageFile += ".png";


		}
	}


}

void FootballZombie::animate(RenderWindow& window) {

	int current;

	check += 0.5;

	if (state == "wait") {
		return;
	}

	if (state == "killed") {

		current = (int)check % 20;

		imageFile = "assets/Zombies/NormalZombie/BoomDie/BoomDie_" + to_string(current);
		imageFile += ".png";

	}

	if (health > 180) {
		if (state == "move")
		{

			current = (int)check % 21;

			imageFile = "assets/Zombies/ConeheadZombie/ConeheadZombie/ConeheadZombie_" + to_string(current);
			imageFile += ".png";
		}

		else if (state == "stop") {
			current = (int)check % 11;

			imageFile = "assets/Zombies/ConeheadZombie/ConeheadZombieAttack/ConeheadZombieAttack_" + to_string(current);
			imageFile += ".png";
		}
	}

	else if (health > 80) {

		head = 0;

		if (state == "move") {

			current = (int)check % 22;

			imageFile = "assets/Zombies/NormalZombie/Zombie/Zombie_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % 21;

			imageFile = "assets/Zombies/NormalZombie/ZombieAttack/ZombieAttack_" + to_string(current);
			imageFile += ".png";
		}

	}
	else {

		if (head < 12) {

			head += 0.46;
			current = (head);

			imageFile = "assets/Zombies/NormalZombie/ZombieHead/ZombieHead_" + to_string(current);
			imageFile += ".png";

			texture.loadFromFile(imageFile);
			zombieSprite.setTexture(texture);
			zombieSprite.setPosition(posx + 50, posy);
			window.draw(zombieSprite);

		}

		if (state == "move") {

			current = (int)check % (18);

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHead/ZombieLostHead_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % (11);

			imageFile = "assets/Zombies/NormalZombie/ZombieLostHeadAttack/ZombieLostHeadAttack_" + to_string(current);
			imageFile += ".png";
		}
		else {

			current = (int)check % (10);

			if (check > 9.5)
				death();

			imageFile = "assets/Zombies/NormalZombie/ZombieDie/ZombieDie_" + to_string(current);
			imageFile += ".png";

		}
	}
}

void DancingZombie::update(RenderWindow& window) {
	if (state == "wait") {
		timer += 0.23;

		if (timer > spawnTime) {
			state = "move";
			timer = 0;
			return;
		}
	}

	// prints zombie on the window
	if (state == "move" || state == "moveup" || state == "movedown") {
		timer++;

		
		if (slow >= 0) {
			timer -= 0.5;
			slow -= 1;
		}

		posx = (timer - spawnTime) * -2 + 1000 - 90;

		if (posx > pixelx)
			return;

	}

	if (changeTimer-- <= 0 && state == "move") {
		if (rand() % 2 == 1) {
			state = "moveup";

			//to check out of bound situation
			if (posy < 200)
				state = "movedown";
		}
		else {
			state = "movedown";
			if (posy > 500)
				state = "moveup";
		}
	}

	if (state == "moveup") {
		posy -= 5;
		if (posy <= oldy - 100) {
			oldy = posy;
			state = "move";
			changeTimer =  + 100;
		}

	}
	else if (state == "movedown") {
		posy += 5;
		if (posy >= oldy + 100) {
			oldy = posy;
			state = "move";
			changeTimer =  + 100;
		}
	}
	animate(window);

	texture.loadFromFile(imageFile);
	zombieSprite.setTexture(texture);
	zombieSprite.setPosition(posx, posy);
	window.draw(zombieSprite);

}

void DancingZombie::animate(RenderWindow& window) {
	int current;

	check += 0.5;

	if (state == "wait") {
		return;
	}

	if (state == "killed") {

		current = (int)check % 20;

		imageFile = "assets/Zombies/NormalZombie/BoomDie/BoomDie_" + to_string(current);
		imageFile += ".png";

	}

	else if (health > 80) {

		head = 0;

		if (state == "move" || state == "moveup" || state == "movedown") {

			current = (int)check % 12;

			imageFile = "assets/Zombies/FlagZombie/FlagZombie/FlagZombie_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % 11;

			imageFile = "assets/Zombies/FlagZombie/FlagZombieAttack/FlagZombieAttack_" + to_string(current);
			imageFile += ".png";
		}

	}
	else {

		if (head < 11) {

			head += 0.46;
			current = (head);

			imageFile = "assets/Zombies/NormalZombie/ZombieHead/ZombieHead_" + to_string(current);
			imageFile += ".png";

			texture.loadFromFile(imageFile);
			zombieSprite.setTexture(texture);
			zombieSprite.setPosition(posx + 50, posy);
			window.draw(zombieSprite);

		}

		if (state == "move" || state == "moveup" || state == "movedown") {

			current = (int)check % (12);

			imageFile = "assets/Zombies/FlagZombie/FlagZombieLostHead/FlagZombieLostHead_" + to_string(current);
			imageFile += ".png";
		}
		else if (state == "stop") {
			current = (int)check % (11);

			imageFile = "assets/Zombies/FlagZombie/FlagZombieLostHeadAttack/ZFlagZombieLostHeadAttack_" + to_string(current);
			imageFile += ".png";
		}
		else {

			current = (int)check % (10);

			if (check > 5)
				death();

			imageFile = "assets/Zombies/NormalZombie/ZombieDie/ZombieDie_" + to_string(current);
			imageFile += ".png";


		}
	}


}

void ZombieFactory::addZombie(int count, string* available, int availableSize) {
	Zombie** temp = new Zombie * [count + size];

	for (int i = 0; i < size; i++) {
		temp[i] = list[i];
	}

	for (int i = size; i < size + count; i++) {

		//randomly add the provided number of zombies
		int random = rand() % availableSize;

		if (random == 0)
			temp[i] = new SimpleZombie();
		else if (random == 1)
			temp[i] = new FootballZombie;
		else if(random == 2)
			temp[i] = new DancingZombie;
		else
			temp[i] = new Zombie();
	}

	delete[] list; // Free old memory
	list = temp;   // Update list with new memory
	size += count;
}

void ZombieFactory::update(RenderWindow& window) {
	for (int i = 0; i < size; i++) {
		list[i]->update(window);

		if (list[i]->checkKilled()) {
			delete list[i];
			
			for (int j = i; j < size - 1; j++) {
				list[j] = list[j + 1];
			}

			size--;
		}
	}
}

int* ZombieFactory::getCoordinates(int num) {

	int x = list[num]->getX();
	int y = list[num]->getY();

	int *coordinates = new int[4]{ x, y, x + list[num]->getWidth(), y + list[num]->getHeight() };

	return coordinates;
}

void ZombieFactory::killed(int num) {
	list[num]->killed();
}

void ZombieFactory::checkCollisionPlant() {
	PlantFactory* plant = PlantFactory::Instance();

	int row = 5;
	int column = 9;

	static int damageTimer = 0;
	if (damageTimer > 10) {

		//checks collision after some specific time
		damageTimer = 0;

		for (int zombieCount = 0; zombieCount < size; zombieCount++) {

			//chceks if zombie has been spawned
			if (list[zombieCount]->checkState() != "wait") {

				bool collision = false;

				//loops through each plant
				for (int plantrow = 0; plantrow < row; plantrow++) {
					for (int plantcol = 0; plantcol < column; plantcol++) {


						if (plant->plants[plantrow][plantcol] != nullptr) {
							int plantx = plant->plants[plantrow][plantcol]->xPosition;
							int planty = plant->plants[plantrow][plantcol]->yPosition;

							int zombiex = list[zombieCount]->getX() + 70;
							int zombiey = list[zombieCount]->getY();

							int zombiew = list[zombieCount]->getWidth();//width if zombie
							int zombieh = list[zombieCount]->getHeight();//height of zombie

							
							//checks collision
							if (plantx < zombiex + zombiew && plantx + 70 > zombiex && planty + 10 < zombiey + zombieh && planty + 40 > zombiey) {
								

								plant->plants[plantrow][plantcol]->reduceHealth(list[zombieCount]->getDamage());

								//updates zombie
								list[zombieCount]->stopped();
								collision = true;
							}
							

						}
					}

				}
				//checks if there is no collision
				if (list[zombieCount]->checkState() == "stop" && !collision) {
					cout << "move" << endl;

					list[zombieCount]->move();
				}
			}
		}

	}

	damageTimer++;

}

bool ZombieFactory::ateBrain() {
	for (int i = 0; i < size; i++) {
		if (list[i]->getX() < 170)
			return true;
	}

	return false;
}

void ZombieFactory::draw(RenderWindow & window) {
	for (int i = 0; i < size; i++) {
		list[i]->draw(window);

		if (list[i]->checkKilled()) {
			delete list[i];

			for (int j = i; j < size - 1; j++) {
				list[j] = list[j + 1];
			}

			size--;
		}
	}
}


void Zombie::draw(RenderWindow& window) {
	if (state == "wait") {

		if (timer > spawnTime) {
			state = "move";
			timer = 0;
			return;
		}
	}

	// prints zombie on the window
	if (state == "move") {

		//checks slow
		if (slow >= 0) {
			timer -= 0.5;
			slow -= 1;
		}

		posx = (timer - spawnTime) * -2 + 1000 - 90;

		if (posx > pixelx)
			return;

	}

	//draw zombie
	texture.loadFromFile(imageFile);
	zombieSprite.setTexture(texture);
	zombieSprite.setPosition(posx, posy);
	window.draw(zombieSprite);
}