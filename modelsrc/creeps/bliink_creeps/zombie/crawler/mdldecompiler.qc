$modelname "creeps/lane_creeps/creep_bad_ranged_diretide/creep_bad_ranged_"
$model "default" "Cube.smd"
$origin 0 200 0

$poseparameter turn -1.00 1.00
$cdmaterials ""
$hboxset "default"
$hbox 0 "wrist_R" -26.297  -8.993  -8.158  2.471  5.239  15.472
$hbox 0 "elbow_R" -25.530  -4.827  -5.551  -0.395  6.788  5.854
$hbox 0 "bicep_R" -31.220  -4.298  -13.298  5.519  8.686  4.892
$hbox 0 "wrist_L" -2.470  -5.240  -15.468  26.296  8.993  8.164
$hbox 0 "elbow_L" 0.401  -6.786  -5.854  25.538  4.827  5.547
$hbox 0 "bicep_L" -5.524  -8.685  -4.895  31.216  4.293  13.296
$hbox 0 "spine2" 4.544  -5.551  19.140  12.989  5.553  22.754
$hbox 0 "spine1" -7.608  -17.374  -15.478  22.403  17.369  18.183
$hboxset "hands"
$hbox 0 "wrist_R" -26.297  -8.993  -8.158  2.471  5.239  15.472
$hbox 0 "wrist_L" -2.470  -5.240  -15.468  26.296  8.993  8.164
$hboxset "select_low"
$hbox 0 "root" -28.771  -32.568  -21.600  31.494  32.570  61.220
$hboxset "select_high"
$hbox 0 "root" -20.134  -17.312  -5.665  14.740  17.314  51.889
$attachment "attach_attack1" "wrist_R" -10.00 0.00 0.00 rotate 0.00 0.00 0.00
$attachment "attach_attack2" "wrist_L" 10.00 0.00 0.00 rotate 0.00 0.00 0.00
$attachment "attach_hitloc" "spine1" 0.00 0.00 0.00 rotate 0.00 0.00 0.00
$surfaceprop "default"
$keyvalues  {  } 
$illumposition -12.200 0.068 29.613
$sequence BindPose "BindPose" fps 30.00
$sequence bad_ranged_diretide_idle "bad_ranged_diretide_idle" loop ACT_DOTA_IDLE 1 fps 30.00
$sequence bad_ranged_diretide_spawn "bad_ranged_diretide_spawn" ACT_DOTA_SPAWN 1 fps 30.00
$sequence bad_ranged_diretide_attack "bad_ranged_diretide_attack" ACT_DOTA_ATTACK 1 fps 30.00 {
  { event AE_DOTA_PLAY_SOUND_ATTACK 15 }
}

$sequence bad_ranged_diretide_attack2 "bad_ranged_diretide_attack2" ACT_DOTA_ATTACK2 1 fps 30.00 {
  { event AE_DOTA_PLAY_SOUND_ATTACK 15 }
}

$sequence bad_ranged_diretide_death "bad_ranged_diretide_death" ACT_DOTA_DIE 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 22 "Creep_Dire.Footstep" }
  { event AE_CL_CREATE_PARTICLE_EFFECT 39 "Z_D1 start_at_attachment attach_hitloc" }
}

$sequence bad_ranged_diretide_death2 "bad_ranged_diretide_death2" ACT_DOTA_DIE 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 30 "Creep_Dire.Footstep" }
  { event AE_CL_CREATE_PARTICLE_EFFECT 52 "Z_D1 start_at_attachment attach_hitloc" }
}

$sequence bliink_crawler_run "bliink_crawler_run" walkframe 19 LX loop ACT_DOTA_RUN 1 fps 30.00
$sequence bad_ranged_diretide_portrait "bad_ranged_diretide_portrait" loop ACT_DOTA_CAPTURE 1 fps 30.00
$sequence bad_ranged_diretide_stun "bad_ranged_diretide_stun" loop ACT_DOTA_DISABLED 1 fps 30.00
$sequence bad_ranged_diretide_flail "bad_ranged_diretide_flail" loop ACT_DOTA_FLAIL 1 fps 30.00
