#include "jazz.h"
#include "rock.h"
#include "metal.h"
#include "kpop.h"


int RockBand::play(MusicBand *other)
{
    int score,remaining_energy;
    const KPopBand* kpop_ = dynamic_cast<KPopBand*>(other);
    const RockBand* rock_ = dynamic_cast<RockBand*>(other);
    const MetalBand* metal_ = dynamic_cast<MetalBand*>(other);
    const JazzBand* jazz_ = dynamic_cast<JazzBand*>(other);
    if(kpop_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.5);
    else if(rock_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.0);
    else if(metal_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(1.4);
    else if(jazz_ != NULL) score = (get_fan_count()+ 0.1* get_talent()* get_energy())*(0.8);
    remaining_energy = (get_energy() - get_energy()*(0.1));
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    return score;
}

void RockBand::rehearse(void) 
{
    int remaining_energy,talent;
    remaining_energy = get_energy() - get_energy()*(0.5 * 0.1);
    talent = get_talent() + 10;
    if(remaining_energy < 0) set_energy(0);
    else set_energy(remaining_energy);
    set_talent(talent);
    
}