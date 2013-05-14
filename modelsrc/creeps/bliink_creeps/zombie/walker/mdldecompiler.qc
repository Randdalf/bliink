$cd "C:\Users\Adam\Desktop"
$modelname "creeps/lane_creeps/creep_bad_melee_diretide/creep_bad_melee_di"
$model "default" "creep_bad_melee_diretide_model.dmx.smd"

$poseparameter turn -1.00 1.00
$cdmaterials ""
$hboxset "default"
$hbox 0 "wrist_R" -26.297  -8.993  -8.158  2.471  5.239  15.472
$hbox 0 "elbow_R" -25.530  -4.827  -5.551  -0.395  6.788  5.854
$hbox 0 "bicep_R" -31.220  -4.298  -13.298  5.519  8.686  4.892
$hbox 0 "wrist_L" -2.470  -5.240  -15.468  26.296  8.993  8.164
$hbox 0 "elbow_L" 0.401  -6.786  -5.854  25.538  4.827  5.547
$hbox 0 "bicep_L" -5.524  -8.685  -4.895  31.216  4.293  13.296
$hbox 0 "head" -5.426  -10.159  -25.127  16.981  10.158  13.555
$hbox 0 "spine2" 4.544  -5.551  19.140  12.989  5.553  22.754
$hbox 0 "spine1" -7.608  -17.374  -15.478  22.403  17.369  18.183
$hbox 0 "ankle_R" -12.440  -3.147  -4.499  1.992  6.847  8.577
$hbox 0 "knee_R" -33.045  -7.925  -2.963  0.182  6.851  9.379
$hbox 0 "thigh_R" -32.591  -5.948  -13.609  -4.780  6.421  4.665
$hbox 0 "ankle_L" -1.991  -6.849  -8.576  12.458  3.161  4.513
$hbox 0 "knee_L" -0.181  -6.851  -9.379  33.042  7.925  2.963
$hbox 0 "thigh_L" 4.808  -6.421  -4.665  32.591  5.948  13.610
$hbox 0 "hip1_0" -8.827  -14.545  -17.308  13.406  13.773  10.354
$hboxset "hands"
$hbox 0 "wrist_R" -26.297  -8.993  -8.158  2.471  5.239  15.472
$hbox 0 "wrist_L" -2.470  -5.240  -15.468  26.296  8.993  8.164
$hboxset "head"
$hbox 0 "head" -5.426  -10.159  -25.127  16.981  10.158  13.555
$hboxset "feet"
$hbox 0 "ankle_R" -12.440  -3.147  -4.499  1.992  6.847  8.577
$hbox 0 "ankle_L" -1.991  -6.849  -8.576  12.458  3.161  4.513
$hboxset "select_high"
$hbox 0 "hip1_0" -13.930  -17.699  -72.564  20.944  16.927  -8.325
$hbox 0 "root" -20.134  -17.312  -5.665  14.740  17.314  51.889
$hboxset "select_low"
$hbox 0 "root" -28.771  -39.230  -82.514  31.494  39.232  58.124
$attachment "attach_attack1" "wrist_R" 0.00 0.00 0.00 rotate -0.00 -0.00 -0.00
$attachment "attach_attack2" "wrist_L" 0.00 0.00 0.00 rotate 0.00 0.00 0.00
$attachment "attach_hitloc" "spine1" 0.00 0.00 0.00 rotate -0.00 0.00 0.00
$surfaceprop "default"
$keyvalues  {  } 
$illumposition 11.159 0.001 69.153
$sequence BindPose "BindPose" fps 30.00
$sequence bliink_walker_run "bliink_walker_run" walkframe 27 LX loop ACT_DOTA_RUN 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 3 "Creep_Dire.Footstep" }
  { event AE_CL_PLAYSOUND 15 "Creep_Dire.Footstep" }
}

$sequence bliink_walker_run_alt "bliink_walker_run_alt" walkframe 21 LX loop ACT_DOTA_RUN 1 fps 30.00 {
  { event AE_CL_PLAYSOUND 0 "Creep_Dire.Footstep" }
  { event AE_CL_PLAYSOUND 12 "Creep_Dire.Footstep" }
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