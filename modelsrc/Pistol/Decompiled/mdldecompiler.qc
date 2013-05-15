$cd "C:\Users\James\Documents"
$modelname "weapons\v_pist_deagle.mdl"
$model "studio" "deagle_reference.smd"

$model "hands" "../hands/hands_reference.smd"

$cdmaterials "models\weapons\V_models\pist_deagle\"
$cdmaterials "models\weapons\v_models\hands\"
$hboxset "default"
$hbox 0 "v_weapon.Deagle_Slide" -0.613  -0.781  -1.760  0.472  0.809  5.787
$hbox 0 "v_weapon.Hands_parent" -4.654  -1.415  0.000  6.834  1.302  6.902
$hbox 0 "v_weapon.Left_Arm" -0.319  -1.833  -1.434  8.563  1.491  1.708
$hbox 0 "v_weapon.Left_Hand" -0.998  -1.856  -1.460  3.655  1.901  1.020
$hbox 0 "v_weapon.Left_Thumb01" -0.038  -0.957  -1.026  2.195  0.816  0.689
$hbox 0 "v_weapon.Left_Thumb_02" -0.557  -0.812  -0.925  1.705  0.536  0.541
$hbox 0 "v_weapon.Left_Pinky01" -0.563  -0.567  -0.680  1.253  1.426  0.518
$hbox 0 "v_weapon.Left_Ring01" -0.051  -0.398  -0.616  1.498  0.636  0.413
$hbox 0 "v_weapon.L_wrist_helper" -0.805  -6.918  -1.161  1.745  0.000  2.128
$hbox 0 "v_weapon.Right_Arm" -0.402  -1.437  -1.576  8.544  1.387  1.609
$hbox 0 "v_weapon.Right_Hand" -0.402  -1.775  -1.494  3.638  1.715  0.913
$hbox 0 "v_weapon.Right_Thumb01" -0.867  -1.013  -1.300  2.356  1.051  0.852
$hbox 0 "v_weapon.Right_Thumb02" -1.285  -0.580  -0.979  1.751  0.994  0.680
$hbox 0 "v_weapon.Right_Middle01" -0.061  -0.689  -0.475  1.376  0.379  0.545
$hbox 0 "v_weapon.Right_Ring01" -0.256  -0.648  -0.542  1.312  0.423  0.473
$hbox 0 "v_weapon.Right_Pinky01" -0.456  -1.085  -0.539  1.124  0.488  0.691
$hbox 0 "v_weapon.R_wrist_helper" -1.175  -7.124  -1.587  1.829  0.933  2.029
$attachment "1" "v_weapon.Deagle_Parent" 0.00 2.75 6.50 rotate -0.00 0.00 0.00
$attachment "2" "v_weapon.Deagle_Parent" 0.00 2.90 0.00 rotate -10.00 -180.00 0.00
$surfaceprop "default"
$illumposition 5.962 3.334 -8.123
$sequence idle1 "idle1" ACT_VM_IDLE 1 fps 16.00
$sequence shoot1 "shoot1" ACT_VM_PRIMARYATTACK 1 fps 40.00 {
  { event 5001 0 "1" }
  { event AE_CLIENT_EFFECT_ATTACH 0 "EjectBrass_9mm 2 100" }
}

$sequence shoot2 "shoot2" ACT_VM_PRIMARYATTACK 1 fps 40.00 {
  { event 5001 0 "1" }
  { event AE_CLIENT_EFFECT_ATTACH 0 "EjectBrass_9mm 2 100" }
}

$sequence shoot_empty "shoot_empty" ACT_VM_DRYFIRE 1 fps 40.00 {
  { event 5001 0 "21" }
}

$sequence reload "reload" ACT_VM_RELOAD 1 fps 30.00 {
  { event 5004 0 "Weapon_DEagle.Slideback" }
  { event 5004 14 "Weapon_DEagle.Clipout" }
  { event 5004 34 "Weapon_DEagle.Clipin" }
}

$sequence draw "draw" ACT_VM_DRAW 1 fps 30.00 {
  { event 5004 1 "Weapon_DEagle.Deploy" }
}

