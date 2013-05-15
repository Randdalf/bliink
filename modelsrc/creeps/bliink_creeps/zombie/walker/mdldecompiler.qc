$modelname "creeps/lane_creeps/bliink_walkerr"

$scale 0.5

$model "default" "bliink_walker.smd"

$poseparameter turn -1.00 1.00
$cdmaterials "models\creeps\neutral_creeps\"
$hboxset "default"

$attachment "attach_attack1" "wrist_R" 0.00 0.00 0.00 rotate -0.00 -0.00 -0.00
$attachment "attach_attack2" "wrist_L" 0.00 0.00 0.00 rotate 0.00 0.00 0.00
$attachment "attach_hitloc" "spine1" 0.00 0.00 0.00 rotate -0.00 0.00 0.00
$surfaceprop "default"
$keyvalues  {  } 
$illumposition 11.159 0.001 69.153
$sequence BindPose "BindPose" fps 30.00
$sequence bad_melee_diretide_run "bad_melee_diretide_run" walkframe 27 LX loop ACT_DOTA_RUN 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 3 "Creep_Dire.Footstep" }
  { event AE_CL_PLAYSOUND 15 "Creep_Dire.Footstep" }
}

$sequence bad_melee_diretide_idle "bad_melee_diretide_idle" loop ACT_DOTA_IDLE 1 fps 30.00
$sequence bad_melee_diretide_death "bad_melee_diretide_death" ACT_DOTA_DIE 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 25 "Creep_Dire.Footstep" }
  { event AE_CL_CREATE_PARTICLE_EFFECT 48 "Z_D1 start_at_attachment attach_hitloc" }
}

$sequence bad_melee_diretide_death_forward "bad_melee_diretide_death_forward" ACT_DOTA_DIE 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 25 "Creep_Dire.Footstep" }
  { event AE_CL_CREATE_PARTICLE_EFFECT 40 "Z_D1 start_at_attachment attach_hitloc" }
}

$sequence bad_melee_diretide_death_backwards "bad_melee_diretide_death_backwards" ACT_DOTA_DIE 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 46 "Creep_Dire.Footstep" }
  { event AE_CL_CREATE_PARTICLE_EFFECT 62 "Z_D1 start_at_attachment attach_hitloc" }
}

$sequence bad_melee_diretide_attack "bad_melee_diretide_attack" ACT_DOTA_ATTACK 1 fps 30.00 {
  { event AE_DOTA_PLAY_SOUND_ATTACK 11 }
}

$sequence bad_melee_diretide_attack2 "bad_melee_diretide_attack2" ACT_DOTA_ATTACK 1 fps 30.00 {
  { event AE_DOTA_PLAY_SOUND_ATTACK 11 }
}

$sequence bad_melee_diretide_attack3 "bad_melee_diretide_attack3" ACT_DOTA_ATTACK 1 fps 30.00 {
  { event AE_DOTA_PLAY_SOUND_ATTACK 12 }
}

$sequence bad_melee_diretide_stun "bad_melee_diretide_stun" loop ACT_DOTA_DISABLED 1 fps 30.00
$sequence bad_melee_diretide_flail "bad_melee_diretide_flail" loop ACT_DOTA_FLAIL 1 fps 30.00
$sequence bad_melee_diretide_spawn "bad_melee_diretide_spawn" ACT_DOTA_SPAWN 1 fps 30.00