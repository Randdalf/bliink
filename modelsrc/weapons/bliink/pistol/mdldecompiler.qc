$modelname "weapons\v_bliink_pistol.mdl"
$model "studio" "w_pist_deagle.002.smd"
$origin 80 0 0

$cdmaterials "models\weapons\w_models\w_bliink_pistol\"
$cdmaterials "models\weapons\v_models\hands\"
$hboxset "default"
$attachment "1" "v_weapon.Deagle_Parent" 0.00 2.75 6.50 rotate -0.00 0.00 0.00
$attachment "2" "v_weapon.Deagle_Parent" 0.00 2.90 0.00 rotate -10.00 -180.00 0.00
$surfaceprop "default"
$illumposition 5.962 3.334 -8.123
$sequence idle1 "idle1" ACT_VM_IDLE 1 fps 16.00 rotate 90
$sequence shoot1 "shoot1" ACT_VM_PRIMARYATTACK 1 fps 40.00 {
  { event 5001 0 "1" }
  { event AE_CLIENT_EFFECT_ATTACH 0 "EjectBrass_9mm 2 100" }
}

$sequence shoot2 "shoot2" ACT_VM_PRIMARYATTACK 1 fps 40.00 rotate 90 {
  { event 5001 0 "1" }
  { event AE_CLIENT_EFFECT_ATTACH 0 "EjectBrass_9mm 2 100" }
}

$sequence shoot_empty "shoot_empty" ACT_VM_DRYFIRE 1 fps 40.00 rotate 90 {
  { event 5001 0 "21" }
}

$sequence reload "reload" ACT_VM_RELOAD 1 fps 30.00 rotate 90 {
  { event 5004 0 "Weapon_DEagle.Slideback" }
  { event 5004 14 "Weapon_DEagle.Clipout" }
  { event 5004 34 "Weapon_DEagle.Clipin" }
}

$sequence draw "draw" ACT_VM_DRAW 1 fps 30.00 rotate 90 {
  { event 5004 1 "Weapon_DEagle.Deploy" }
}

