#include "jazz.h"
#include "rock.h"
#include "metal.h"
#include "kpop.h"


int MetalBand::play(MusicBand *other)
{
    int score,remaining_energy;
    KPopBand* kpop_ = dynamic_cast<KPopBand*>(other);
    RockBand* rock_ = dynamic_cast<RockBand*>(other);
    MetalBand* metal_ = dynamic_cast<MetalBand*>(other);
    JazzBand* jazz_ = dynamic_cast<JazzBand*>(other);
    if(kpop_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.5);
    else if(rock_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.5);
    else if(metal_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.0);
    else if(jazz_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.1);
    remaining_energy = (get_energy() - get_energy()*(0.16));
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    return score;
}

void MetalBand::rehearse(void) 
{
    int remaining_energy,talent;
    remaining_energy = get_energy() - get_energy()*(0.5 * 0.16);
    talent = get_talent() - 5;
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    if(talent < 0) set_talent(0);
    else set_talent(talent);
    
}