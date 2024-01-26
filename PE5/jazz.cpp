#include "jazz.h"
#include "rock.h"
#include "metal.h"
#include "kpop.h"


int JazzBand::play(MusicBand *other)
{
    int score,remaining_energy;
    KPopBand* kpop_ = dynamic_cast<KPopBand*>(other);
    RockBand* rock_ = dynamic_cast<RockBand*>(other);
    MetalBand* metal_ = dynamic_cast<MetalBand*>(other);
    JazzBand* jazz_ = dynamic_cast<JazzBand*>(other);
    if(kpop_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.5);
    else if(rock_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.7);
    else if(metal_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.3);
    else if(jazz_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.7);
    remaining_energy = (get_energy() - get_energy()*(0.06));
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    return score;
}

void JazzBand::rehearse(void) 
{
    int remaining_energy,talent;
    remaining_energy = get_energy() - get_energy()*(0.5 * 0.06);
    talent = get_talent() + 5;
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    set_talent(talent);

    
}