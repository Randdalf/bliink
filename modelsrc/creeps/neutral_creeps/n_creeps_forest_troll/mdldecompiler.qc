$cd "C:\Program Files (x86)\Steam\steamapps\sourcemods\projectbliink\modelsrc\creeps\neutral_creeps\n_creeps_forest_troll"
$modelname "creeps/neutral_creeps/n_creeps_forest_troll/bliink_creep_forest_troll.mdl"

$scale 0.5

$model "default" "n_creep_forest_troll_high_priest_model.dmx.smd"

$cdmaterials ""
$hboxset "default"
$hbox 0 "root" -15.111  -18.224  -12.022  20.696  18.447  29.043
$hbox 0 "front_flap2_0" -1.655  -12.701  -4.898  14.125  12.711  0.000
$hbox 0 "thigh_R" -44.914  -7.944  -10.150  4.593  6.410  34.007
$hbox 0 "spine1" -16.609  -17.756  -28.685  26.322  17.596  11.708
$hbox 0 "thigh_L" -6.329  -8.989  -33.560  44.914  7.944  10.156
$hbox 0 "back_cloth3_0" 0.000  -19.120  -2.295  36.974  17.679  16.222
$hbox 0 "front_flap2_1" -5.973  -12.701  -17.384  2.746  12.711  7.076
$hbox 0 "knee_R" -32.557  -7.312  -7.087  6.320  7.152  8.816
$hbox 0 "ankle_R" -15.410  -8.722  -30.637  7.859  9.077  10.864
$hbox 0 "toeBase_R" -15.020  -8.985  -31.828  12.431  11.470  2.839
$hbox 0 "spine2" -26.809  -20.421  -32.533  31.282  20.097  13.531
$hbox 0 "spine3" -3.281  -14.299  -20.764  18.195  14.288  10.964
$hbox 0 "clavicle_R" -32.965  -11.247  -9.869  13.386  19.330  25.761
$hbox 0 "neck1" 0.000  -5.963  -6.760  10.466  5.932  0.000
$hbox 0 "necklace1_0" -17.266  -14.044  -14.877  13.448  12.487  0.421
$hbox 0 "clavicle_L" -13.583  -15.559  -23.437  33.094  11.134  9.060
$hbox 0 "bicep_R" -47.739  -13.849  -9.258  7.107  8.133  15.580
$hbox 0 "elbow_R" -43.877  -6.489  -7.201  2.897  8.133  7.136
$hbox 0 "wrist_R" -24.606  -7.819  -13.893  55.907  20.228  10.914
$hbox 0 "Rhand_club_1" -43.867  -44.002  -21.631  108.171  17.264  19.043
$hbox 0 "head" -29.280  -13.498  -18.191  18.630  13.498  18.196
$hbox 0 "R_ear1_0_R" -13.156  -3.061  -4.641  6.565  12.529  7.503
$hbox 0 "L_ear0_0_L" -3.576  -13.837  -7.002  11.452  4.836  4.596
$hbox 0 "hair_base0_0" -33.393  -6.474  -17.756  11.442  5.112  17.237
$hbox 0 "Jaw" -9.093  -13.314  -15.846  17.868  13.314  7.171
$hbox 0 "R_ear1_1_R" -7.648  -3.764  -8.804  8.312  16.194  8.491
$hbox 0 "L_ear0_1_L" -12.033  -13.837  -5.019  12.855  4.836  4.596
$hbox 0 "hair_three6_0" 0.000  -5.379  -3.188  10.669  4.472  16.359
$hbox 0 "hair_two5_0" -1.715  -5.255  -5.557  14.275  3.764  17.179
$hbox 0 "hair_one4_0" -0.350  -3.722  -2.226  20.044  5.286  18.595
$hbox 0 "hair_four7_0" -4.784  -6.874  -2.931  6.201  5.037  15.074
$hbox 0 "necklace1_1" -8.345  -9.933  -3.725  16.272  9.752  4.846
$hbox 0 "bicep_L" -5.076  -7.468  -12.428  40.574  9.454  9.242
$hbox 0 "elbow_L" -25.468  -8.213  -7.136  43.877  6.406  7.201
$hbox 0 "wrist_L" 0.000  -6.614  -10.914  24.606  7.819  8.029
$hbox 0 "knee_L" -6.320  -7.152  -8.816  32.557  7.312  7.087
$hbox 0 "ankle_L" -7.859  -9.077  -10.864  15.410  8.722  30.637
$hbox 0 "toeBase_L" -12.431  -11.470  -2.839  15.020  8.985  31.828
$hbox 0 "back_cloth3_1" -1.052  -20.842  -39.745  9.570  20.917  20.507
$attachment "attach_attack1" "Rhand_club_1" 85.00 -20.00 0.00 rotate 0.00 -0.00 0.00
$attachment "attach_hitloc" "spine3" 0.00 0.00 0.00 rotate -0.00 -0.00 0.00
$surfaceprop "default"
$keyvalues  {  } 
$illumposition -11.221 -11.859 103.768
$sequence BindPose "BindPose" fps 30.00
$sequence run "n_creep_troll_high_priest_run" walkframe 25 LX loop ACT_RUN 1 fps 30.00
$sequence idle "n_creep_forest_troll_high_priest_idle" loop ACT_DOTA_IDLE 1 fps 30.00
$sequence attack "n_creep_forest_troll_high_priest_attack" ACT_DOTA_ATTACK 1 fps 30.00
$sequence death "n_creep_forest_troll_high_priest_death" ACT_DOTA_DIE 1 fps 30.00

