#include "Controller.h"
#include <cmath>
#include <iostream>
namespace mrsd
{
	void Controller::control(const mrsd::Game& g, float t)
	{
        if (p == 0){
            return;
        }       
        
        if (!p->dead){
            
            determineSafeSpots(g);
            int safe_x = pickSafeSpot(g);
            p->x = p->x + safe_x*g.playerSpeed;

            for(int i =p->x -5; i<=p->x+5;i++){
                std::cout << dangerZonePred[i]  <<" ";
            }
            std::cout<<std::endl;
        
        }            
	}

	void Controller::createPlayer(Game& g)
	{
		if(p == 0)
		{
			p = new Player();
			p->dead = true;
		}
		if(p->dead)
		{
			p->dead = false;
			p->x = g.getWidth()/2;
			g.newPlayer(p);
		}
	}

	Prediction Controller::trackProjectile(const Projectile& p, const Game& g)
	{
		Prediction pred;
         
        float gravity = g.getGravity();
        float temp_t; 
        float a = .5f*gravity; time;
        float b = p.vy;
        float c = p.y;
                float game_t = g.getGameTime();
        temp_t = (-b + sqrt(pow(b,2)-4*a*c))/(2*a); //quadratic equation 
        if (temp_t < 0) {
            temp_t = (-b - sqrt(pow(b,2)-4*a*c))/(2*a);
        }
        pred.t = temp_t;
        pred.x = p.x + p.vx * pred.t;
    
		return pred;
	}

	void Controller::determineSafeSpots(const Game& g)
	{
        std::list<Projectile> projectiles = g.getProjectiles();
        std::list<Explosion> explosions = g.getExplosions();
        int w = g.getWidth();
        float explosionSize = g.explosionSize;

        for(int i = 0; i < w; ++i) {
            dangerZonePred[i] = 0;       
        }

        for(std::list<Projectile>::iterator it = projectiles.begin();
            it != projectiles.end(); it++){
            Prediction pred = trackProjectile(*it, g);    
     
            for(int i = std::floor(pred.x - 1.5*explosionSize);
              i <= std::ceil(pred.x + 1.5*explosionSize); ++i)
            {
                if( i >= 0 && i <= w ){
                    dangerZonePred[i] = 1;  
                }
            }       
        }

        for(std::list<Explosion>::iterator it = explosions.begin();
        it != explosions.end();it++){
            for(int i = std::floor(it->x - 1.5*explosionSize);
                i <= std::ceil(it->x + 1.5*explosionSize); ++i){
                if( i >= 0 && i <= w ){
                    dangerZonePred[i] = -1;
                }
            }
        }            
        
	}

	int Controller::pickSafeSpot(const Game& g)
	{
        if(dangerZonePred[int(p->x)]==0) return 0;
        int w = g.getWidth();            
        int l = p->x;
        int r = p->x;
        
        while (l > 0 || r < w) {
            std::cout <<r << " " << l << std::endl;
            if (l > 0 && dangerZonePred[l] == 0){
                std::cout << "left " << l << " " << r << std::endl;
                return -1;
            }
            if (r < w && dangerZonePred[r] == 0){
                std::cout << "right "<<r << " " << l << std::endl;
                return 1;
            }
            r++;
            l--;
        }
        return 0;
	}
}
