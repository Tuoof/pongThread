#include <iostream>
#include <thread>
#include <random>
#include <chrono>

using namespace std;

class Player
{
private:
	enum PlayerEnum
	{
		PlayerX,
		PlayerY
	};
	PlayerEnum selector;

	float Hits;

public:
	void setPlayerX();
	void setPlayerY();
	void setHits(float);
	float getHits();

	PlayerEnum getPlayer()
	{
		return selector;
	}
};

void Player::setPlayerX()
{
	selector = PlayerEnum::PlayerX;
}

void Player::setPlayerY()
{
	selector = PlayerEnum::PlayerY;
}

void Player::setHits(float hit)
{
	Hits = hit;
}

float Player::getHits()
{
	return Hits;
}

class Score
{
public:
	Score(int X, int Y);
	void setXscore(int X);
	void setYscore(int Y);
	int getXscore();
	int getYscore();

protected:
	int PlayerXscore;
	int PlayerYscore;
};

Score::Score(int X, int Y)
{
	PlayerXscore = X;
	PlayerYscore = Y;
}

void Score::setXscore(int X)
{
	PlayerXscore += X;
}

void Score::setYscore(int Y)
{
	PlayerYscore += Y;
}

int Score::getXscore()
{
	return PlayerXscore;
}

int Score::getYscore()
{
	return PlayerYscore;
}

Player playerX;
Player playerY;
Score *score = new Score(0, 0);
    
// random_device rd;
// mt19937 gen(rd());

unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::default_random_engine gen(seed);

void PlayerTurn(Player p)
{
    if (p.getPlayer() == 0)
    {
        cout  <<"PlayerX Turn" << endl;

        uniform_int_distribution<> dis(1, 100);
        int random = dis(gen);

        cout << "Random Hits X = " << random << endl << endl;
        p.setHits(random);

        if (p.getHits() <= 50)
        {
            score->setYscore(1);
            cout << "SCORE" << endl;
            cout << "Player X = " << score->getXscore() << " |  Player Y = " << score->getYscore() << endl << endl;
        }
        else if (p.getHits() > 50)
        {
            cout << "Repeat from opponent" << endl << endl;
        }
    }

    else if (p.getPlayer() == 1)
    {
        cout <<"PlayerY Turn" << endl;
        
        uniform_int_distribution<> dis(1, 100);
        int random = dis(gen);

        cout << "Random Hits Y = " << random << endl << endl;
        p.setHits(random);

        if (p.getHits() <= 50)
        {
            score->setXscore(1);
            cout << "SCORE" << endl;
            cout << "Player X = " << score->getXscore() << " |  Player Y = " << score->getYscore() << endl << endl;
        }
        else if (p.getHits() > 50)
        {
            cout << "Repeat from opponent" << endl << endl;
        }
    }
}

int main()
{
    playerX.setPlayerX();
    playerY.setPlayerY();

    uniform_int_distribution<> dis(1, 2);

    if (dis(gen) == 1)
    {
        cout << "Player X first" << endl<<endl;

        do
        {
            thread playerXThread(PlayerTurn, playerX);
            playerXThread.join();
            thread playerYThread(PlayerTurn, playerY);
            playerYThread.join();
        }
        while (score->getXscore()<10 && score->getYscore()<10);
    }

    else if (dis(gen) == 2)
    {
        cout << "Player Y move first." << endl << endl;

        do
        {
            thread playerYThread(PlayerTurn, playerY);
            playerYThread.join();
            thread playerXThread(PlayerTurn, playerX);
            playerXThread.join();
        }
        while (score->getXscore() < 10 && score->getYscore() < 10);
    }

    if (score->getXscore() == 10)
    {
        cout << endl << "Player X Win!" << endl;
    }
    else if (score->getYscore() == 10)
    {
        cout << endl << "Player Y Win!" << endl;
    }

    delete score;
    return 0;
}
