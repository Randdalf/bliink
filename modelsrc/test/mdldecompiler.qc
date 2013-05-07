$cd "C:\Program Files (x86)\Steam\steamapps\sourcemods\projectbliink\modelsrc\test\"
$modelname "player\sdk_player_shared.mdl"
$poseparameter body_pitch -46.10 88.43
$poseparameter body_yaw -50.81 45.01
$poseparameter body_height 28.00 58.00
$poseparameter move_y -1.00 1.00
$poseparameter move_x -1.00 1.00
$cdmaterials "models\player\animation/"
$hboxset "default"
$hbox 0 "ValveBiped.Bip01_Pelvis" -3.890  -0.000  -2.982  3.890  3.345  0.000
$hbox 0 "ValveBiped.Bip01_Spine4" 0.000  -0.000  -1.938  3.307  1.001  1.938
$hbox 0 "ValveBiped.Bip01_L_Hand" 0.000  -2.717  -1.192  8.387  0.047  47.381
$hbox 0 "ValveBiped.Bip01_R_Hand" 0.000  -2.717  -1.331  8.387  0.050  47.381
$attachment "weapon_bone" "ValveBiped.weapon_bone" 0.00 0.00 -0.00 rotate -0.00 -0.00 -0.00
$attachment "weapon_bone_left" "ValveBiped.weapon_bone_left" 0.00 0.00 0.00 rotate 0.00 0.00 -0.00
$attachment "anim_attachment_RH" "ValveBiped.Bip01_R_Hand" 0.00 0.00 -0.00 rotate 0.00 -0.00 -0.00
$surfaceprop "default"
$illumposition 25.810 12.146 30.691
$sequence ragdollspawn "ragdollspawn" fps 30.00
$animation mdldecompiler_delta.smd "mdldecompiler_delta.smd" fps 30
$animation a_aimmatrix_idle_straight_up "a_aimmatrix_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_up_right "a_aimmatrix_idle_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mid_right "a_aimmatrix_idle_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_down_right "a_aimmatrix_idle_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_straight_up "a_aimmatrix_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_up_center "a_aimmatrix_idle_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mid_center "a_aimmatrix_idle_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_down_center "a_aimmatrix_idle_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_straight_up "a_aimmatrix_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_up_left "a_aimmatrix_idle_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mid_left "a_aimmatrix_idle_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_down_left "a_aimmatrix_idle_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle "a_aimmatrix_idle_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_straight_up a_aimmatrix_idle_up_right a_aimmatrix_idle_mid_right a_aimmatrix_idle_down_right a_aimmatrix_idle_straight_up a_aimmatrix_idle_up_center a_aimmatrix_idle_mid_center a_aimmatrix_idle_down_center a_aimmatrix_idle_straight_up a_aimmatrix_idle_up_left a_aimmatrix_idle_mid_left a_aimmatrix_idle_down_left
}
$animation a_aimmatrix_idle_aim_straight_up "a_aimmatrix_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_up_right "a_aimmatrix_idle_aim_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mid_right "a_aimmatrix_idle_aim_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_down_right "a_aimmatrix_idle_aim_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_straight_up "a_aimmatrix_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_up_center "a_aimmatrix_idle_aim_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mid_center "a_aimmatrix_idle_aim_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_down_center "a_aimmatrix_idle_aim_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_straight_up "a_aimmatrix_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_up_left "a_aimmatrix_idle_aim_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mid_left "a_aimmatrix_idle_aim_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_down_left "a_aimmatrix_idle_aim_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_aim "a_aimmatrix_idle_aim_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_aim_straight_up a_aimmatrix_idle_aim_up_right a_aimmatrix_idle_aim_mid_right a_aimmatrix_idle_aim_down_right a_aimmatrix_idle_aim_straight_up a_aimmatrix_idle_aim_up_center a_aimmatrix_idle_aim_mid_center a_aimmatrix_idle_aim_down_center a_aimmatrix_idle_aim_straight_up a_aimmatrix_idle_aim_up_left a_aimmatrix_idle_aim_mid_left a_aimmatrix_idle_aim_down_left
}
$animation a_aimmatrix_crouch_idle_straight_up "a_aimmatrix_crouch_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_up_right "a_aimmatrix_crouch_idle_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mid_right "a_aimmatrix_crouch_idle_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_down_right "a_aimmatrix_crouch_idle_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_straight_up "a_aimmatrix_crouch_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_up_center "a_aimmatrix_crouch_idle_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mid_center "a_aimmatrix_crouch_idle_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_down_center "a_aimmatrix_crouch_idle_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_straight_up "a_aimmatrix_crouch_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_up_left "a_aimmatrix_crouch_idle_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mid_left "a_aimmatrix_crouch_idle_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_down_left "a_aimmatrix_crouch_idle_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle "a_aimmatrix_crouch_idle_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_straight_up a_aimmatrix_crouch_idle_up_right a_aimmatrix_crouch_idle_mid_right a_aimmatrix_crouch_idle_down_right a_aimmatrix_crouch_idle_straight_up a_aimmatrix_crouch_idle_up_center a_aimmatrix_crouch_idle_mid_center a_aimmatrix_crouch_idle_down_center a_aimmatrix_crouch_idle_straight_up a_aimmatrix_crouch_idle_up_left a_aimmatrix_crouch_idle_mid_left a_aimmatrix_crouch_idle_down_left
}
$animation a_aimmatrix_crouch_idle_aim_straight_up "a_aimmatrix_crouch_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_up_right "a_aimmatrix_crouch_idle_aim_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mid_right "a_aimmatrix_crouch_idle_aim_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_down_right "a_aimmatrix_crouch_idle_aim_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_straight_up "a_aimmatrix_crouch_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_up_center "a_aimmatrix_crouch_idle_aim_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mid_center "a_aimmatrix_crouch_idle_aim_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_down_center "a_aimmatrix_crouch_idle_aim_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_straight_up "a_aimmatrix_crouch_idle_aim_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_up_left "a_aimmatrix_crouch_idle_aim_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mid_left "a_aimmatrix_crouch_idle_aim_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_down_left "a_aimmatrix_crouch_idle_aim_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_aim "a_aimmatrix_crouch_idle_aim_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_aim_straight_up a_aimmatrix_crouch_idle_aim_up_right a_aimmatrix_crouch_idle_aim_mid_right a_aimmatrix_crouch_idle_aim_down_right a_aimmatrix_crouch_idle_aim_straight_up a_aimmatrix_crouch_idle_aim_up_center a_aimmatrix_crouch_idle_aim_mid_center a_aimmatrix_crouch_idle_aim_down_center a_aimmatrix_crouch_idle_aim_straight_up a_aimmatrix_crouch_idle_aim_up_left a_aimmatrix_crouch_idle_aim_mid_left a_aimmatrix_crouch_idle_aim_down_left
}
$animation a_aimmatrix_crouch_walk_straight_up "a_aimmatrix_crouch_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_up_right "a_aimmatrix_crouch_walk_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mid_right "a_aimmatrix_crouch_walk_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_down_right "a_aimmatrix_crouch_walk_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_straight_up "a_aimmatrix_crouch_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_up_center "a_aimmatrix_crouch_walk_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mid_center "a_aimmatrix_crouch_walk_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_down_center "a_aimmatrix_crouch_walk_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_straight_up "a_aimmatrix_crouch_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_up_left "a_aimmatrix_crouch_walk_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mid_left "a_aimmatrix_crouch_walk_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_down_left "a_aimmatrix_crouch_walk_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk "a_aimmatrix_crouch_walk_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_straight_up a_aimmatrix_crouch_walk_up_right a_aimmatrix_crouch_walk_mid_right a_aimmatrix_crouch_walk_down_right a_aimmatrix_crouch_walk_straight_up a_aimmatrix_crouch_walk_up_center a_aimmatrix_crouch_walk_mid_center a_aimmatrix_crouch_walk_down_center a_aimmatrix_crouch_walk_straight_up a_aimmatrix_crouch_walk_up_left a_aimmatrix_crouch_walk_mid_left a_aimmatrix_crouch_walk_down_left
}
$animation a_aimmatrix_walk_straight_up "a_aimmatrix_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_up_right "a_aimmatrix_walk_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mid_right "a_aimmatrix_walk_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_down_right "a_aimmatrix_walk_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_straight_up "a_aimmatrix_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_up_center "a_aimmatrix_walk_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mid_center "a_aimmatrix_walk_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_down_center "a_aimmatrix_walk_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_straight_up "a_aimmatrix_walk_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_up_left "a_aimmatrix_walk_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mid_left "a_aimmatrix_walk_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_down_left "a_aimmatrix_walk_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk "a_aimmatrix_walk_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_straight_up a_aimmatrix_walk_up_right a_aimmatrix_walk_mid_right a_aimmatrix_walk_down_right a_aimmatrix_walk_straight_up a_aimmatrix_walk_up_center a_aimmatrix_walk_mid_center a_aimmatrix_walk_down_center a_aimmatrix_walk_straight_up a_aimmatrix_walk_up_left a_aimmatrix_walk_mid_left a_aimmatrix_walk_down_left
}
$animation a_aimmatrix_run_straight_up "a_aimmatrix_run_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_up_right "a_aimmatrix_run_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mid_right "a_aimmatrix_run_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_down_right "a_aimmatrix_run_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_straight_up "a_aimmatrix_run_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_up_center "a_aimmatrix_run_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mid_center "a_aimmatrix_run_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_down_center "a_aimmatrix_run_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_straight_up "a_aimmatrix_run_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_up_left "a_aimmatrix_run_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mid_left "a_aimmatrix_run_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_down_left "a_aimmatrix_run_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run "a_aimmatrix_run_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_straight_up a_aimmatrix_run_up_right a_aimmatrix_run_mid_right a_aimmatrix_run_down_right a_aimmatrix_run_straight_up a_aimmatrix_run_up_center a_aimmatrix_run_mid_center a_aimmatrix_run_down_center a_aimmatrix_run_straight_up a_aimmatrix_run_up_left a_aimmatrix_run_mid_left a_aimmatrix_run_down_left
}
$animation a_aimmatrix_prone_idle_straight_up "a_aimmatrix_prone_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_up_right "a_aimmatrix_prone_idle_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mid_right "a_aimmatrix_prone_idle_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_down_right "a_aimmatrix_prone_idle_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_straight_up "a_aimmatrix_prone_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_up_center "a_aimmatrix_prone_idle_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mid_center "a_aimmatrix_prone_idle_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_down_center "a_aimmatrix_prone_idle_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_straight_up "a_aimmatrix_prone_idle_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_up_left "a_aimmatrix_prone_idle_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mid_left "a_aimmatrix_prone_idle_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_down_left "a_aimmatrix_prone_idle_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle "a_aimmatrix_prone_idle_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_straight_up a_aimmatrix_prone_idle_up_right a_aimmatrix_prone_idle_mid_right a_aimmatrix_prone_idle_down_right a_aimmatrix_prone_idle_straight_up a_aimmatrix_prone_idle_up_center a_aimmatrix_prone_idle_mid_center a_aimmatrix_prone_idle_down_center a_aimmatrix_prone_idle_straight_up a_aimmatrix_prone_idle_up_left a_aimmatrix_prone_idle_mid_left a_aimmatrix_prone_idle_down_left
}
$animation a_aimmatrix_idle_mg42_straight_up "a_aimmatrix_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_up_right "a_aimmatrix_idle_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_mid_right "a_aimmatrix_idle_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_down_right "a_aimmatrix_idle_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_straight_up "a_aimmatrix_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_up_center "a_aimmatrix_idle_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_mid_center "a_aimmatrix_idle_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_down_center "a_aimmatrix_idle_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_straight_up "a_aimmatrix_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_up_left "a_aimmatrix_idle_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_mid_left "a_aimmatrix_idle_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_mg42_down_left "a_aimmatrix_idle_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_mg42 "a_aimmatrix_idle_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_mg42_straight_up a_aimmatrix_idle_mg42_up_right a_aimmatrix_idle_mg42_mid_right a_aimmatrix_idle_mg42_down_right a_aimmatrix_idle_mg42_straight_up a_aimmatrix_idle_mg42_up_center a_aimmatrix_idle_mg42_mid_center a_aimmatrix_idle_mg42_down_center a_aimmatrix_idle_mg42_straight_up a_aimmatrix_idle_mg42_up_left a_aimmatrix_idle_mg42_mid_left a_aimmatrix_idle_mg42_down_left
}
$animation a_aimmatrix_idle_aim_mg42_straight_up "a_aimmatrix_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_up_right "a_aimmatrix_idle_aim_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_mid_right "a_aimmatrix_idle_aim_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_down_right "a_aimmatrix_idle_aim_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_straight_up "a_aimmatrix_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_up_center "a_aimmatrix_idle_aim_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_mid_center "a_aimmatrix_idle_aim_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_down_center "a_aimmatrix_idle_aim_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_straight_up "a_aimmatrix_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_up_left "a_aimmatrix_idle_aim_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_mid_left "a_aimmatrix_idle_aim_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_mg42_down_left "a_aimmatrix_idle_aim_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_aim_mg42 "a_aimmatrix_idle_aim_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_aim_mg42_straight_up a_aimmatrix_idle_aim_mg42_up_right a_aimmatrix_idle_aim_mg42_mid_right a_aimmatrix_idle_aim_mg42_down_right a_aimmatrix_idle_aim_mg42_straight_up a_aimmatrix_idle_aim_mg42_up_center a_aimmatrix_idle_aim_mg42_mid_center a_aimmatrix_idle_aim_mg42_down_center a_aimmatrix_idle_aim_mg42_straight_up a_aimmatrix_idle_aim_mg42_up_left a_aimmatrix_idle_aim_mg42_mid_left a_aimmatrix_idle_aim_mg42_down_left
}
$animation a_aimmatrix_crouch_idle_mg42_straight_up "a_aimmatrix_crouch_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_up_right "a_aimmatrix_crouch_idle_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_mid_right "a_aimmatrix_crouch_idle_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_down_right "a_aimmatrix_crouch_idle_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_straight_up "a_aimmatrix_crouch_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_up_center "a_aimmatrix_crouch_idle_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_mid_center "a_aimmatrix_crouch_idle_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_down_center "a_aimmatrix_crouch_idle_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_straight_up "a_aimmatrix_crouch_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_up_left "a_aimmatrix_crouch_idle_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_mid_left "a_aimmatrix_crouch_idle_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_mg42_down_left "a_aimmatrix_crouch_idle_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_mg42 "a_aimmatrix_crouch_idle_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_mg42_straight_up a_aimmatrix_crouch_idle_mg42_up_right a_aimmatrix_crouch_idle_mg42_mid_right a_aimmatrix_crouch_idle_mg42_down_right a_aimmatrix_crouch_idle_mg42_straight_up a_aimmatrix_crouch_idle_mg42_up_center a_aimmatrix_crouch_idle_mg42_mid_center a_aimmatrix_crouch_idle_mg42_down_center a_aimmatrix_crouch_idle_mg42_straight_up a_aimmatrix_crouch_idle_mg42_up_left a_aimmatrix_crouch_idle_mg42_mid_left a_aimmatrix_crouch_idle_mg42_down_left
}
$animation a_aimmatrix_crouch_idle_aim_mg42_straight_up "a_aimmatrix_crouch_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_up_right "a_aimmatrix_crouch_idle_aim_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_mid_right "a_aimmatrix_crouch_idle_aim_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_down_right "a_aimmatrix_crouch_idle_aim_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_straight_up "a_aimmatrix_crouch_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_up_center "a_aimmatrix_crouch_idle_aim_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_mid_center "a_aimmatrix_crouch_idle_aim_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_down_center "a_aimmatrix_crouch_idle_aim_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_straight_up "a_aimmatrix_crouch_idle_aim_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_up_left "a_aimmatrix_crouch_idle_aim_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_mid_left "a_aimmatrix_crouch_idle_aim_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_mg42_down_left "a_aimmatrix_crouch_idle_aim_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_aim_mg42 "a_aimmatrix_crouch_idle_aim_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_aim_mg42_straight_up a_aimmatrix_crouch_idle_aim_mg42_up_right a_aimmatrix_crouch_idle_aim_mg42_mid_right a_aimmatrix_crouch_idle_aim_mg42_down_right a_aimmatrix_crouch_idle_aim_mg42_straight_up a_aimmatrix_crouch_idle_aim_mg42_up_center a_aimmatrix_crouch_idle_aim_mg42_mid_center a_aimmatrix_crouch_idle_aim_mg42_down_center a_aimmatrix_crouch_idle_aim_mg42_straight_up a_aimmatrix_crouch_idle_aim_mg42_up_left a_aimmatrix_crouch_idle_aim_mg42_mid_left a_aimmatrix_crouch_idle_aim_mg42_down_left
}
$animation a_aimmatrix_crouch_walk_mg42_straight_up "a_aimmatrix_crouch_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_up_right "a_aimmatrix_crouch_walk_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_mid_right "a_aimmatrix_crouch_walk_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_down_right "a_aimmatrix_crouch_walk_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_straight_up "a_aimmatrix_crouch_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_up_center "a_aimmatrix_crouch_walk_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_mid_center "a_aimmatrix_crouch_walk_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_down_center "a_aimmatrix_crouch_walk_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_straight_up "a_aimmatrix_crouch_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_up_left "a_aimmatrix_crouch_walk_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_mid_left "a_aimmatrix_crouch_walk_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_mg42_down_left "a_aimmatrix_crouch_walk_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk_mg42 "a_aimmatrix_crouch_walk_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_mg42_straight_up a_aimmatrix_crouch_walk_mg42_up_right a_aimmatrix_crouch_walk_mg42_mid_right a_aimmatrix_crouch_walk_mg42_down_right a_aimmatrix_crouch_walk_mg42_straight_up a_aimmatrix_crouch_walk_mg42_up_center a_aimmatrix_crouch_walk_mg42_mid_center a_aimmatrix_crouch_walk_mg42_down_center a_aimmatrix_crouch_walk_mg42_straight_up a_aimmatrix_crouch_walk_mg42_up_left a_aimmatrix_crouch_walk_mg42_mid_left a_aimmatrix_crouch_walk_mg42_down_left
}
$animation a_aimmatrix_walk_mg42_straight_up "a_aimmatrix_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_up_right "a_aimmatrix_walk_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_mid_right "a_aimmatrix_walk_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_down_right "a_aimmatrix_walk_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_straight_up "a_aimmatrix_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_up_center "a_aimmatrix_walk_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_mid_center "a_aimmatrix_walk_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_down_center "a_aimmatrix_walk_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_straight_up "a_aimmatrix_walk_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_up_left "a_aimmatrix_walk_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_mid_left "a_aimmatrix_walk_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_mg42_down_left "a_aimmatrix_walk_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk_mg42 "a_aimmatrix_walk_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_mg42_straight_up a_aimmatrix_walk_mg42_up_right a_aimmatrix_walk_mg42_mid_right a_aimmatrix_walk_mg42_down_right a_aimmatrix_walk_mg42_straight_up a_aimmatrix_walk_mg42_up_center a_aimmatrix_walk_mg42_mid_center a_aimmatrix_walk_mg42_down_center a_aimmatrix_walk_mg42_straight_up a_aimmatrix_walk_mg42_up_left a_aimmatrix_walk_mg42_mid_left a_aimmatrix_walk_mg42_down_left
}
$animation a_aimmatrix_run_mg42_straight_up "a_aimmatrix_run_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_up_right "a_aimmatrix_run_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_mid_right "a_aimmatrix_run_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_down_right "a_aimmatrix_run_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_straight_up "a_aimmatrix_run_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_up_center "a_aimmatrix_run_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_mid_center "a_aimmatrix_run_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_down_center "a_aimmatrix_run_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_straight_up "a_aimmatrix_run_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_up_left "a_aimmatrix_run_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_mid_left "a_aimmatrix_run_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_mg42_down_left "a_aimmatrix_run_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run_mg42 "a_aimmatrix_run_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_mg42_straight_up a_aimmatrix_run_mg42_up_right a_aimmatrix_run_mg42_mid_right a_aimmatrix_run_mg42_down_right a_aimmatrix_run_mg42_straight_up a_aimmatrix_run_mg42_up_center a_aimmatrix_run_mg42_mid_center a_aimmatrix_run_mg42_down_center a_aimmatrix_run_mg42_straight_up a_aimmatrix_run_mg42_up_left a_aimmatrix_run_mg42_mid_left a_aimmatrix_run_mg42_down_left
}
$animation a_aimmatrix_prone_idle_mg42_straight_up "a_aimmatrix_prone_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_up_right "a_aimmatrix_prone_idle_mg42_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_mid_right "a_aimmatrix_prone_idle_mg42_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_down_right "a_aimmatrix_prone_idle_mg42_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_straight_up "a_aimmatrix_prone_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_up_center "a_aimmatrix_prone_idle_mg42_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_mid_center "a_aimmatrix_prone_idle_mg42_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_down_center "a_aimmatrix_prone_idle_mg42_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_straight_up "a_aimmatrix_prone_idle_mg42_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_up_left "a_aimmatrix_prone_idle_mg42_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_mid_left "a_aimmatrix_prone_idle_mg42_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_mg42_down_left "a_aimmatrix_prone_idle_mg42_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle_mg42 "a_aimmatrix_prone_idle_mg42_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_mg42_straight_up a_aimmatrix_prone_idle_mg42_up_right a_aimmatrix_prone_idle_mg42_mid_right a_aimmatrix_prone_idle_mg42_down_right a_aimmatrix_prone_idle_mg42_straight_up a_aimmatrix_prone_idle_mg42_up_center a_aimmatrix_prone_idle_mg42_mid_center a_aimmatrix_prone_idle_mg42_down_center a_aimmatrix_prone_idle_mg42_straight_up a_aimmatrix_prone_idle_mg42_up_left a_aimmatrix_prone_idle_mg42_mid_left a_aimmatrix_prone_idle_mg42_down_left
}
$animation a_aimmatrix_idle_30cal_straight_up "a_aimmatrix_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_up_right "a_aimmatrix_idle_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_mid_right "a_aimmatrix_idle_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_down_right "a_aimmatrix_idle_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_straight_up "a_aimmatrix_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_up_center "a_aimmatrix_idle_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_mid_center "a_aimmatrix_idle_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_down_center "a_aimmatrix_idle_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_straight_up "a_aimmatrix_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_up_left "a_aimmatrix_idle_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_mid_left "a_aimmatrix_idle_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_30cal_down_left "a_aimmatrix_idle_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_30cal "a_aimmatrix_idle_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_30cal_straight_up a_aimmatrix_idle_30cal_up_right a_aimmatrix_idle_30cal_mid_right a_aimmatrix_idle_30cal_down_right a_aimmatrix_idle_30cal_straight_up a_aimmatrix_idle_30cal_up_center a_aimmatrix_idle_30cal_mid_center a_aimmatrix_idle_30cal_down_center a_aimmatrix_idle_30cal_straight_up a_aimmatrix_idle_30cal_up_left a_aimmatrix_idle_30cal_mid_left a_aimmatrix_idle_30cal_down_left
}
$animation a_aimmatrix_idle_aim_30cal_straight_up "a_aimmatrix_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_up_right "a_aimmatrix_idle_aim_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_mid_right "a_aimmatrix_idle_aim_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_down_right "a_aimmatrix_idle_aim_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_straight_up "a_aimmatrix_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_up_center "a_aimmatrix_idle_aim_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_mid_center "a_aimmatrix_idle_aim_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_down_center "a_aimmatrix_idle_aim_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_straight_up "a_aimmatrix_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_up_left "a_aimmatrix_idle_aim_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_mid_left "a_aimmatrix_idle_aim_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_30cal_down_left "a_aimmatrix_idle_aim_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_aim_30cal "a_aimmatrix_idle_aim_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_aim_30cal_straight_up a_aimmatrix_idle_aim_30cal_up_right a_aimmatrix_idle_aim_30cal_mid_right a_aimmatrix_idle_aim_30cal_down_right a_aimmatrix_idle_aim_30cal_straight_up a_aimmatrix_idle_aim_30cal_up_center a_aimmatrix_idle_aim_30cal_mid_center a_aimmatrix_idle_aim_30cal_down_center a_aimmatrix_idle_aim_30cal_straight_up a_aimmatrix_idle_aim_30cal_up_left a_aimmatrix_idle_aim_30cal_mid_left a_aimmatrix_idle_aim_30cal_down_left
}
$animation a_aimmatrix_crouch_idle_30cal_straight_up "a_aimmatrix_crouch_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_up_right "a_aimmatrix_crouch_idle_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_mid_right "a_aimmatrix_crouch_idle_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_down_right "a_aimmatrix_crouch_idle_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_straight_up "a_aimmatrix_crouch_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_up_center "a_aimmatrix_crouch_idle_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_mid_center "a_aimmatrix_crouch_idle_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_down_center "a_aimmatrix_crouch_idle_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_straight_up "a_aimmatrix_crouch_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_up_left "a_aimmatrix_crouch_idle_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_mid_left "a_aimmatrix_crouch_idle_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_30cal_down_left "a_aimmatrix_crouch_idle_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_30cal "a_aimmatrix_crouch_idle_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_30cal_straight_up a_aimmatrix_crouch_idle_30cal_up_right a_aimmatrix_crouch_idle_30cal_mid_right a_aimmatrix_crouch_idle_30cal_down_right a_aimmatrix_crouch_idle_30cal_straight_up a_aimmatrix_crouch_idle_30cal_up_center a_aimmatrix_crouch_idle_30cal_mid_center a_aimmatrix_crouch_idle_30cal_down_center a_aimmatrix_crouch_idle_30cal_straight_up a_aimmatrix_crouch_idle_30cal_up_left a_aimmatrix_crouch_idle_30cal_mid_left a_aimmatrix_crouch_idle_30cal_down_left
}
$animation a_aimmatrix_crouch_idle_aim_30cal_straight_up "a_aimmatrix_crouch_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_up_right "a_aimmatrix_crouch_idle_aim_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_mid_right "a_aimmatrix_crouch_idle_aim_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_down_right "a_aimmatrix_crouch_idle_aim_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_straight_up "a_aimmatrix_crouch_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_up_center "a_aimmatrix_crouch_idle_aim_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_mid_center "a_aimmatrix_crouch_idle_aim_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_down_center "a_aimmatrix_crouch_idle_aim_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_straight_up "a_aimmatrix_crouch_idle_aim_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_up_left "a_aimmatrix_crouch_idle_aim_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_mid_left "a_aimmatrix_crouch_idle_aim_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_30cal_down_left "a_aimmatrix_crouch_idle_aim_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_aim_30cal "a_aimmatrix_crouch_idle_aim_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_aim_30cal_straight_up a_aimmatrix_crouch_idle_aim_30cal_up_right a_aimmatrix_crouch_idle_aim_30cal_mid_right a_aimmatrix_crouch_idle_aim_30cal_down_right a_aimmatrix_crouch_idle_aim_30cal_straight_up a_aimmatrix_crouch_idle_aim_30cal_up_center a_aimmatrix_crouch_idle_aim_30cal_mid_center a_aimmatrix_crouch_idle_aim_30cal_down_center a_aimmatrix_crouch_idle_aim_30cal_straight_up a_aimmatrix_crouch_idle_aim_30cal_up_left a_aimmatrix_crouch_idle_aim_30cal_mid_left a_aimmatrix_crouch_idle_aim_30cal_down_left
}
$animation a_aimmatrix_crouch_walk_30cal_straight_up "a_aimmatrix_crouch_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_up_right "a_aimmatrix_crouch_walk_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_mid_right "a_aimmatrix_crouch_walk_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_down_right "a_aimmatrix_crouch_walk_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_straight_up "a_aimmatrix_crouch_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_up_center "a_aimmatrix_crouch_walk_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_mid_center "a_aimmatrix_crouch_walk_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_down_center "a_aimmatrix_crouch_walk_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_straight_up "a_aimmatrix_crouch_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_up_left "a_aimmatrix_crouch_walk_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_mid_left "a_aimmatrix_crouch_walk_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_30cal_down_left "a_aimmatrix_crouch_walk_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk_30cal "a_aimmatrix_crouch_walk_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_30cal_straight_up a_aimmatrix_crouch_walk_30cal_up_right a_aimmatrix_crouch_walk_30cal_mid_right a_aimmatrix_crouch_walk_30cal_down_right a_aimmatrix_crouch_walk_30cal_straight_up a_aimmatrix_crouch_walk_30cal_up_center a_aimmatrix_crouch_walk_30cal_mid_center a_aimmatrix_crouch_walk_30cal_down_center a_aimmatrix_crouch_walk_30cal_straight_up a_aimmatrix_crouch_walk_30cal_up_left a_aimmatrix_crouch_walk_30cal_mid_left a_aimmatrix_crouch_walk_30cal_down_left
}
$animation a_aimmatrix_walk_30cal_straight_up "a_aimmatrix_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_up_right "a_aimmatrix_walk_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_mid_right "a_aimmatrix_walk_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_down_right "a_aimmatrix_walk_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_straight_up "a_aimmatrix_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_up_center "a_aimmatrix_walk_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_mid_center "a_aimmatrix_walk_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_down_center "a_aimmatrix_walk_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_straight_up "a_aimmatrix_walk_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_up_left "a_aimmatrix_walk_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_mid_left "a_aimmatrix_walk_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_30cal_down_left "a_aimmatrix_walk_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk_30cal "a_aimmatrix_walk_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_30cal_straight_up a_aimmatrix_walk_30cal_up_right a_aimmatrix_walk_30cal_mid_right a_aimmatrix_walk_30cal_down_right a_aimmatrix_walk_30cal_straight_up a_aimmatrix_walk_30cal_up_center a_aimmatrix_walk_30cal_mid_center a_aimmatrix_walk_30cal_down_center a_aimmatrix_walk_30cal_straight_up a_aimmatrix_walk_30cal_up_left a_aimmatrix_walk_30cal_mid_left a_aimmatrix_walk_30cal_down_left
}
$animation a_aimmatrix_run_30cal_straight_up "a_aimmatrix_run_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_up_right "a_aimmatrix_run_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_mid_right "a_aimmatrix_run_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_down_right "a_aimmatrix_run_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_straight_up "a_aimmatrix_run_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_up_center "a_aimmatrix_run_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_mid_center "a_aimmatrix_run_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_down_center "a_aimmatrix_run_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_straight_up "a_aimmatrix_run_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_up_left "a_aimmatrix_run_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_mid_left "a_aimmatrix_run_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_30cal_down_left "a_aimmatrix_run_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run_30cal "a_aimmatrix_run_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_30cal_straight_up a_aimmatrix_run_30cal_up_right a_aimmatrix_run_30cal_mid_right a_aimmatrix_run_30cal_down_right a_aimmatrix_run_30cal_straight_up a_aimmatrix_run_30cal_up_center a_aimmatrix_run_30cal_mid_center a_aimmatrix_run_30cal_down_center a_aimmatrix_run_30cal_straight_up a_aimmatrix_run_30cal_up_left a_aimmatrix_run_30cal_mid_left a_aimmatrix_run_30cal_down_left
}
$animation a_aimmatrix_prone_idle_30cal_straight_up "a_aimmatrix_prone_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_up_right "a_aimmatrix_prone_idle_30cal_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_mid_right "a_aimmatrix_prone_idle_30cal_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_down_right "a_aimmatrix_prone_idle_30cal_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_straight_up "a_aimmatrix_prone_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_up_center "a_aimmatrix_prone_idle_30cal_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_mid_center "a_aimmatrix_prone_idle_30cal_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_down_center "a_aimmatrix_prone_idle_30cal_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_straight_up "a_aimmatrix_prone_idle_30cal_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_up_left "a_aimmatrix_prone_idle_30cal_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_mid_left "a_aimmatrix_prone_idle_30cal_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_30cal_down_left "a_aimmatrix_prone_idle_30cal_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle_30cal "a_aimmatrix_prone_idle_30cal_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_30cal_straight_up a_aimmatrix_prone_idle_30cal_up_right a_aimmatrix_prone_idle_30cal_mid_right a_aimmatrix_prone_idle_30cal_down_right a_aimmatrix_prone_idle_30cal_straight_up a_aimmatrix_prone_idle_30cal_up_center a_aimmatrix_prone_idle_30cal_mid_center a_aimmatrix_prone_idle_30cal_down_center a_aimmatrix_prone_idle_30cal_straight_up a_aimmatrix_prone_idle_30cal_up_left a_aimmatrix_prone_idle_30cal_mid_left a_aimmatrix_prone_idle_30cal_down_left
}
$animation a_aimmatrix_idle_bazooka_straight_up "a_aimmatrix_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_up_right "a_aimmatrix_idle_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_mid_right "a_aimmatrix_idle_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_down_right "a_aimmatrix_idle_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_straight_up "a_aimmatrix_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_up_center "a_aimmatrix_idle_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_mid_center "a_aimmatrix_idle_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_down_center "a_aimmatrix_idle_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_straight_up "a_aimmatrix_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_up_left "a_aimmatrix_idle_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_mid_left "a_aimmatrix_idle_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_bazooka_down_left "a_aimmatrix_idle_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_bazooka "a_aimmatrix_idle_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_bazooka_straight_up a_aimmatrix_idle_bazooka_up_right a_aimmatrix_idle_bazooka_mid_right a_aimmatrix_idle_bazooka_down_right a_aimmatrix_idle_bazooka_straight_up a_aimmatrix_idle_bazooka_up_center a_aimmatrix_idle_bazooka_mid_center a_aimmatrix_idle_bazooka_down_center a_aimmatrix_idle_bazooka_straight_up a_aimmatrix_idle_bazooka_up_left a_aimmatrix_idle_bazooka_mid_left a_aimmatrix_idle_bazooka_down_left
}
$animation a_aimmatrix_idle_aim_bazooka_straight_up "a_aimmatrix_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_up_right "a_aimmatrix_idle_aim_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_mid_right "a_aimmatrix_idle_aim_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_down_right "a_aimmatrix_idle_aim_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_straight_up "a_aimmatrix_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_up_center "a_aimmatrix_idle_aim_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_mid_center "a_aimmatrix_idle_aim_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_down_center "a_aimmatrix_idle_aim_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_straight_up "a_aimmatrix_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_up_left "a_aimmatrix_idle_aim_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_mid_left "a_aimmatrix_idle_aim_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_bazooka_down_left "a_aimmatrix_idle_aim_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_aim_bazooka "a_aimmatrix_idle_aim_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_aim_bazooka_straight_up a_aimmatrix_idle_aim_bazooka_up_right a_aimmatrix_idle_aim_bazooka_mid_right a_aimmatrix_idle_aim_bazooka_down_right a_aimmatrix_idle_aim_bazooka_straight_up a_aimmatrix_idle_aim_bazooka_up_center a_aimmatrix_idle_aim_bazooka_mid_center a_aimmatrix_idle_aim_bazooka_down_center a_aimmatrix_idle_aim_bazooka_straight_up a_aimmatrix_idle_aim_bazooka_up_left a_aimmatrix_idle_aim_bazooka_mid_left a_aimmatrix_idle_aim_bazooka_down_left
}
$animation a_aimmatrix_crouch_idle_bazooka_straight_up "a_aimmatrix_crouch_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_up_right "a_aimmatrix_crouch_idle_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_mid_right "a_aimmatrix_crouch_idle_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_down_right "a_aimmatrix_crouch_idle_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_straight_up "a_aimmatrix_crouch_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_up_center "a_aimmatrix_crouch_idle_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_mid_center "a_aimmatrix_crouch_idle_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_down_center "a_aimmatrix_crouch_idle_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_straight_up "a_aimmatrix_crouch_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_up_left "a_aimmatrix_crouch_idle_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_mid_left "a_aimmatrix_crouch_idle_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_bazooka_down_left "a_aimmatrix_crouch_idle_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_bazooka "a_aimmatrix_crouch_idle_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_bazooka_straight_up a_aimmatrix_crouch_idle_bazooka_up_right a_aimmatrix_crouch_idle_bazooka_mid_right a_aimmatrix_crouch_idle_bazooka_down_right a_aimmatrix_crouch_idle_bazooka_straight_up a_aimmatrix_crouch_idle_bazooka_up_center a_aimmatrix_crouch_idle_bazooka_mid_center a_aimmatrix_crouch_idle_bazooka_down_center a_aimmatrix_crouch_idle_bazooka_straight_up a_aimmatrix_crouch_idle_bazooka_up_left a_aimmatrix_crouch_idle_bazooka_mid_left a_aimmatrix_crouch_idle_bazooka_down_left
}
$animation a_aimmatrix_crouch_idle_aim_bazooka_straight_up "a_aimmatrix_crouch_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_up_right "a_aimmatrix_crouch_idle_aim_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_mid_right "a_aimmatrix_crouch_idle_aim_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_down_right "a_aimmatrix_crouch_idle_aim_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_straight_up "a_aimmatrix_crouch_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_up_center "a_aimmatrix_crouch_idle_aim_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_mid_center "a_aimmatrix_crouch_idle_aim_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_down_center "a_aimmatrix_crouch_idle_aim_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_straight_up "a_aimmatrix_crouch_idle_aim_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_up_left "a_aimmatrix_crouch_idle_aim_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_mid_left "a_aimmatrix_crouch_idle_aim_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_bazooka_down_left "a_aimmatrix_crouch_idle_aim_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_aim_bazooka "a_aimmatrix_crouch_idle_aim_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_aim_bazooka_straight_up a_aimmatrix_crouch_idle_aim_bazooka_up_right a_aimmatrix_crouch_idle_aim_bazooka_mid_right a_aimmatrix_crouch_idle_aim_bazooka_down_right a_aimmatrix_crouch_idle_aim_bazooka_straight_up a_aimmatrix_crouch_idle_aim_bazooka_up_center a_aimmatrix_crouch_idle_aim_bazooka_mid_center a_aimmatrix_crouch_idle_aim_bazooka_down_center a_aimmatrix_crouch_idle_aim_bazooka_straight_up a_aimmatrix_crouch_idle_aim_bazooka_up_left a_aimmatrix_crouch_idle_aim_bazooka_mid_left a_aimmatrix_crouch_idle_aim_bazooka_down_left
}
$animation a_aimmatrix_crouch_walk_bazooka_straight_up "a_aimmatrix_crouch_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_up_right "a_aimmatrix_crouch_walk_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_mid_right "a_aimmatrix_crouch_walk_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_down_right "a_aimmatrix_crouch_walk_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_straight_up "a_aimmatrix_crouch_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_up_center "a_aimmatrix_crouch_walk_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_mid_center "a_aimmatrix_crouch_walk_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_down_center "a_aimmatrix_crouch_walk_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_straight_up "a_aimmatrix_crouch_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_up_left "a_aimmatrix_crouch_walk_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_mid_left "a_aimmatrix_crouch_walk_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_bazooka_down_left "a_aimmatrix_crouch_walk_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk_bazooka "a_aimmatrix_crouch_walk_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_bazooka_straight_up a_aimmatrix_crouch_walk_bazooka_up_right a_aimmatrix_crouch_walk_bazooka_mid_right a_aimmatrix_crouch_walk_bazooka_down_right a_aimmatrix_crouch_walk_bazooka_straight_up a_aimmatrix_crouch_walk_bazooka_up_center a_aimmatrix_crouch_walk_bazooka_mid_center a_aimmatrix_crouch_walk_bazooka_down_center a_aimmatrix_crouch_walk_bazooka_straight_up a_aimmatrix_crouch_walk_bazooka_up_left a_aimmatrix_crouch_walk_bazooka_mid_left a_aimmatrix_crouch_walk_bazooka_down_left
}
$animation a_aimmatrix_walk_bazooka_straight_up "a_aimmatrix_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_up_right "a_aimmatrix_walk_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_mid_right "a_aimmatrix_walk_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_down_right "a_aimmatrix_walk_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_straight_up "a_aimmatrix_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_up_center "a_aimmatrix_walk_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_mid_center "a_aimmatrix_walk_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_down_center "a_aimmatrix_walk_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_straight_up "a_aimmatrix_walk_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_up_left "a_aimmatrix_walk_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_mid_left "a_aimmatrix_walk_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_bazooka_down_left "a_aimmatrix_walk_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk_bazooka "a_aimmatrix_walk_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_bazooka_straight_up a_aimmatrix_walk_bazooka_up_right a_aimmatrix_walk_bazooka_mid_right a_aimmatrix_walk_bazooka_down_right a_aimmatrix_walk_bazooka_straight_up a_aimmatrix_walk_bazooka_up_center a_aimmatrix_walk_bazooka_mid_center a_aimmatrix_walk_bazooka_down_center a_aimmatrix_walk_bazooka_straight_up a_aimmatrix_walk_bazooka_up_left a_aimmatrix_walk_bazooka_mid_left a_aimmatrix_walk_bazooka_down_left
}
$animation a_aimmatrix_run_bazooka_straight_up "a_aimmatrix_run_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_up_right "a_aimmatrix_run_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_mid_right "a_aimmatrix_run_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_down_right "a_aimmatrix_run_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_straight_up "a_aimmatrix_run_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_up_center "a_aimmatrix_run_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_mid_center "a_aimmatrix_run_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_down_center "a_aimmatrix_run_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_straight_up "a_aimmatrix_run_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_up_left "a_aimmatrix_run_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_mid_left "a_aimmatrix_run_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_bazooka_down_left "a_aimmatrix_run_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run_bazooka "a_aimmatrix_run_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_bazooka_straight_up a_aimmatrix_run_bazooka_up_right a_aimmatrix_run_bazooka_mid_right a_aimmatrix_run_bazooka_down_right a_aimmatrix_run_bazooka_straight_up a_aimmatrix_run_bazooka_up_center a_aimmatrix_run_bazooka_mid_center a_aimmatrix_run_bazooka_down_center a_aimmatrix_run_bazooka_straight_up a_aimmatrix_run_bazooka_up_left a_aimmatrix_run_bazooka_mid_left a_aimmatrix_run_bazooka_down_left
}
$animation a_aimmatrix_prone_idle_bazooka_straight_up "a_aimmatrix_prone_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_up_right "a_aimmatrix_prone_idle_bazooka_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_mid_right "a_aimmatrix_prone_idle_bazooka_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_down_right "a_aimmatrix_prone_idle_bazooka_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_straight_up "a_aimmatrix_prone_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_up_center "a_aimmatrix_prone_idle_bazooka_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_mid_center "a_aimmatrix_prone_idle_bazooka_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_down_center "a_aimmatrix_prone_idle_bazooka_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_straight_up "a_aimmatrix_prone_idle_bazooka_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_up_left "a_aimmatrix_prone_idle_bazooka_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_mid_left "a_aimmatrix_prone_idle_bazooka_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_bazooka_down_left "a_aimmatrix_prone_idle_bazooka_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle_bazooka "a_aimmatrix_prone_idle_bazooka_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_bazooka_straight_up a_aimmatrix_prone_idle_bazooka_up_right a_aimmatrix_prone_idle_bazooka_mid_right a_aimmatrix_prone_idle_bazooka_down_right a_aimmatrix_prone_idle_bazooka_straight_up a_aimmatrix_prone_idle_bazooka_up_center a_aimmatrix_prone_idle_bazooka_mid_center a_aimmatrix_prone_idle_bazooka_down_center a_aimmatrix_prone_idle_bazooka_straight_up a_aimmatrix_prone_idle_bazooka_up_left a_aimmatrix_prone_idle_bazooka_mid_left a_aimmatrix_prone_idle_bazooka_down_left
}
$animation a_aimmatrix_idle_grenade_straight_up "a_aimmatrix_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_up_right "a_aimmatrix_idle_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_mid_right "a_aimmatrix_idle_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_down_right "a_aimmatrix_idle_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_straight_up "a_aimmatrix_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_up_center "a_aimmatrix_idle_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_mid_center "a_aimmatrix_idle_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_down_center "a_aimmatrix_idle_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_straight_up "a_aimmatrix_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_up_left "a_aimmatrix_idle_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_mid_left "a_aimmatrix_idle_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_grenade_down_left "a_aimmatrix_idle_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_grenade "a_aimmatrix_idle_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_grenade_straight_up a_aimmatrix_idle_grenade_up_right a_aimmatrix_idle_grenade_mid_right a_aimmatrix_idle_grenade_down_right a_aimmatrix_idle_grenade_straight_up a_aimmatrix_idle_grenade_up_center a_aimmatrix_idle_grenade_mid_center a_aimmatrix_idle_grenade_down_center a_aimmatrix_idle_grenade_straight_up a_aimmatrix_idle_grenade_up_left a_aimmatrix_idle_grenade_mid_left a_aimmatrix_idle_grenade_down_left
}
$animation a_aimmatrix_crouch_idle_grenade_straight_up "a_aimmatrix_crouch_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_up_right "a_aimmatrix_crouch_idle_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_mid_right "a_aimmatrix_crouch_idle_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_down_right "a_aimmatrix_crouch_idle_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_straight_up "a_aimmatrix_crouch_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_up_center "a_aimmatrix_crouch_idle_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_mid_center "a_aimmatrix_crouch_idle_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_down_center "a_aimmatrix_crouch_idle_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_straight_up "a_aimmatrix_crouch_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_up_left "a_aimmatrix_crouch_idle_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_mid_left "a_aimmatrix_crouch_idle_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_grenade_down_left "a_aimmatrix_crouch_idle_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_grenade "a_aimmatrix_crouch_idle_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_grenade_straight_up a_aimmatrix_crouch_idle_grenade_up_right a_aimmatrix_crouch_idle_grenade_mid_right a_aimmatrix_crouch_idle_grenade_down_right a_aimmatrix_crouch_idle_grenade_straight_up a_aimmatrix_crouch_idle_grenade_up_center a_aimmatrix_crouch_idle_grenade_mid_center a_aimmatrix_crouch_idle_grenade_down_center a_aimmatrix_crouch_idle_grenade_straight_up a_aimmatrix_crouch_idle_grenade_up_left a_aimmatrix_crouch_idle_grenade_mid_left a_aimmatrix_crouch_idle_grenade_down_left
}
$animation a_aimmatrix_crouch_walk_grenade_straight_up "a_aimmatrix_crouch_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_up_right "a_aimmatrix_crouch_walk_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_mid_right "a_aimmatrix_crouch_walk_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_down_right "a_aimmatrix_crouch_walk_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_straight_up "a_aimmatrix_crouch_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_up_center "a_aimmatrix_crouch_walk_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_mid_center "a_aimmatrix_crouch_walk_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_down_center "a_aimmatrix_crouch_walk_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_straight_up "a_aimmatrix_crouch_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_up_left "a_aimmatrix_crouch_walk_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_mid_left "a_aimmatrix_crouch_walk_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_grenade_down_left "a_aimmatrix_crouch_walk_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk_grenade "a_aimmatrix_crouch_walk_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_grenade_straight_up a_aimmatrix_crouch_walk_grenade_up_right a_aimmatrix_crouch_walk_grenade_mid_right a_aimmatrix_crouch_walk_grenade_down_right a_aimmatrix_crouch_walk_grenade_straight_up a_aimmatrix_crouch_walk_grenade_up_center a_aimmatrix_crouch_walk_grenade_mid_center a_aimmatrix_crouch_walk_grenade_down_center a_aimmatrix_crouch_walk_grenade_straight_up a_aimmatrix_crouch_walk_grenade_up_left a_aimmatrix_crouch_walk_grenade_mid_left a_aimmatrix_crouch_walk_grenade_down_left
}
$animation a_aimmatrix_walk_grenade_straight_up "a_aimmatrix_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_up_right "a_aimmatrix_walk_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_mid_right "a_aimmatrix_walk_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_down_right "a_aimmatrix_walk_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_straight_up "a_aimmatrix_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_up_center "a_aimmatrix_walk_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_mid_center "a_aimmatrix_walk_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_down_center "a_aimmatrix_walk_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_straight_up "a_aimmatrix_walk_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_up_left "a_aimmatrix_walk_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_mid_left "a_aimmatrix_walk_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_grenade_down_left "a_aimmatrix_walk_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk_grenade "a_aimmatrix_walk_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_grenade_straight_up a_aimmatrix_walk_grenade_up_right a_aimmatrix_walk_grenade_mid_right a_aimmatrix_walk_grenade_down_right a_aimmatrix_walk_grenade_straight_up a_aimmatrix_walk_grenade_up_center a_aimmatrix_walk_grenade_mid_center a_aimmatrix_walk_grenade_down_center a_aimmatrix_walk_grenade_straight_up a_aimmatrix_walk_grenade_up_left a_aimmatrix_walk_grenade_mid_left a_aimmatrix_walk_grenade_down_left
}
$animation a_aimmatrix_run_grenade_straight_up "a_aimmatrix_run_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_up_right "a_aimmatrix_run_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_mid_right "a_aimmatrix_run_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_down_right "a_aimmatrix_run_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_straight_up "a_aimmatrix_run_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_up_center "a_aimmatrix_run_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_mid_center "a_aimmatrix_run_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_down_center "a_aimmatrix_run_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_straight_up "a_aimmatrix_run_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_up_left "a_aimmatrix_run_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_mid_left "a_aimmatrix_run_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_grenade_down_left "a_aimmatrix_run_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run_grenade "a_aimmatrix_run_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_grenade_straight_up a_aimmatrix_run_grenade_up_right a_aimmatrix_run_grenade_mid_right a_aimmatrix_run_grenade_down_right a_aimmatrix_run_grenade_straight_up a_aimmatrix_run_grenade_up_center a_aimmatrix_run_grenade_mid_center a_aimmatrix_run_grenade_down_center a_aimmatrix_run_grenade_straight_up a_aimmatrix_run_grenade_up_left a_aimmatrix_run_grenade_mid_left a_aimmatrix_run_grenade_down_left
}
$animation a_aimmatrix_prone_idle_grenade_straight_up "a_aimmatrix_prone_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_up_right "a_aimmatrix_prone_idle_grenade_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_mid_right "a_aimmatrix_prone_idle_grenade_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_down_right "a_aimmatrix_prone_idle_grenade_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_straight_up "a_aimmatrix_prone_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_up_center "a_aimmatrix_prone_idle_grenade_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_mid_center "a_aimmatrix_prone_idle_grenade_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_down_center "a_aimmatrix_prone_idle_grenade_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_straight_up "a_aimmatrix_prone_idle_grenade_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_up_left "a_aimmatrix_prone_idle_grenade_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_mid_left "a_aimmatrix_prone_idle_grenade_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_grenade_down_left "a_aimmatrix_prone_idle_grenade_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle_grenade "a_aimmatrix_prone_idle_grenade_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_grenade_straight_up a_aimmatrix_prone_idle_grenade_up_right a_aimmatrix_prone_idle_grenade_mid_right a_aimmatrix_prone_idle_grenade_down_right a_aimmatrix_prone_idle_grenade_straight_up a_aimmatrix_prone_idle_grenade_up_center a_aimmatrix_prone_idle_grenade_mid_center a_aimmatrix_prone_idle_grenade_down_center a_aimmatrix_prone_idle_grenade_straight_up a_aimmatrix_prone_idle_grenade_up_left a_aimmatrix_prone_idle_grenade_mid_left a_aimmatrix_prone_idle_grenade_down_left
}
$animation a_aimmatrix_idle_pistol_straight_up "a_aimmatrix_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_up_right "a_aimmatrix_idle_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_mid_right "a_aimmatrix_idle_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_down_right "a_aimmatrix_idle_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_straight_up "a_aimmatrix_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_up_center "a_aimmatrix_idle_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_mid_center "a_aimmatrix_idle_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_down_center "a_aimmatrix_idle_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_straight_up "a_aimmatrix_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_up_left "a_aimmatrix_idle_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_mid_left "a_aimmatrix_idle_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_pistol_down_left "a_aimmatrix_idle_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_pistol "a_aimmatrix_idle_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_pistol_straight_up a_aimmatrix_idle_pistol_up_right a_aimmatrix_idle_pistol_mid_right a_aimmatrix_idle_pistol_down_right a_aimmatrix_idle_pistol_straight_up a_aimmatrix_idle_pistol_up_center a_aimmatrix_idle_pistol_mid_center a_aimmatrix_idle_pistol_down_center a_aimmatrix_idle_pistol_straight_up a_aimmatrix_idle_pistol_up_left a_aimmatrix_idle_pistol_mid_left a_aimmatrix_idle_pistol_down_left
}
$animation a_aimmatrix_idle_aim_pistol_straight_up "a_aimmatrix_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_up_right "a_aimmatrix_idle_aim_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_mid_right "a_aimmatrix_idle_aim_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_down_right "a_aimmatrix_idle_aim_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_straight_up "a_aimmatrix_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_up_center "a_aimmatrix_idle_aim_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_mid_center "a_aimmatrix_idle_aim_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_down_center "a_aimmatrix_idle_aim_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_straight_up "a_aimmatrix_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_up_left "a_aimmatrix_idle_aim_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_mid_left "a_aimmatrix_idle_aim_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_idle_aim_pistol_down_left "a_aimmatrix_idle_aim_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_idle_aim_pistol "a_aimmatrix_idle_aim_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_idle_aim_pistol_straight_up a_aimmatrix_idle_aim_pistol_up_right a_aimmatrix_idle_aim_pistol_mid_right a_aimmatrix_idle_aim_pistol_down_right a_aimmatrix_idle_aim_pistol_straight_up a_aimmatrix_idle_aim_pistol_up_center a_aimmatrix_idle_aim_pistol_mid_center a_aimmatrix_idle_aim_pistol_down_center a_aimmatrix_idle_aim_pistol_straight_up a_aimmatrix_idle_aim_pistol_up_left a_aimmatrix_idle_aim_pistol_mid_left a_aimmatrix_idle_aim_pistol_down_left
}
$animation a_aimmatrix_crouch_idle_pistol_straight_up "a_aimmatrix_crouch_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_up_right "a_aimmatrix_crouch_idle_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_mid_right "a_aimmatrix_crouch_idle_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_down_right "a_aimmatrix_crouch_idle_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_straight_up "a_aimmatrix_crouch_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_up_center "a_aimmatrix_crouch_idle_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_mid_center "a_aimmatrix_crouch_idle_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_down_center "a_aimmatrix_crouch_idle_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_straight_up "a_aimmatrix_crouch_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_up_left "a_aimmatrix_crouch_idle_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_mid_left "a_aimmatrix_crouch_idle_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_pistol_down_left "a_aimmatrix_crouch_idle_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_pistol "a_aimmatrix_crouch_idle_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_pistol_straight_up a_aimmatrix_crouch_idle_pistol_up_right a_aimmatrix_crouch_idle_pistol_mid_right a_aimmatrix_crouch_idle_pistol_down_right a_aimmatrix_crouch_idle_pistol_straight_up a_aimmatrix_crouch_idle_pistol_up_center a_aimmatrix_crouch_idle_pistol_mid_center a_aimmatrix_crouch_idle_pistol_down_center a_aimmatrix_crouch_idle_pistol_straight_up a_aimmatrix_crouch_idle_pistol_up_left a_aimmatrix_crouch_idle_pistol_mid_left a_aimmatrix_crouch_idle_pistol_down_left
}
$animation a_aimmatrix_crouch_idle_aim_pistol_straight_up "a_aimmatrix_crouch_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_up_right "a_aimmatrix_crouch_idle_aim_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_mid_right "a_aimmatrix_crouch_idle_aim_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_down_right "a_aimmatrix_crouch_idle_aim_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_straight_up "a_aimmatrix_crouch_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_up_center "a_aimmatrix_crouch_idle_aim_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_mid_center "a_aimmatrix_crouch_idle_aim_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_down_center "a_aimmatrix_crouch_idle_aim_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_straight_up "a_aimmatrix_crouch_idle_aim_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_up_left "a_aimmatrix_crouch_idle_aim_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_mid_left "a_aimmatrix_crouch_idle_aim_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_idle_aim_pistol_down_left "a_aimmatrix_crouch_idle_aim_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_idle_aim_pistol "a_aimmatrix_crouch_idle_aim_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_idle_aim_pistol_straight_up a_aimmatrix_crouch_idle_aim_pistol_up_right a_aimmatrix_crouch_idle_aim_pistol_mid_right a_aimmatrix_crouch_idle_aim_pistol_down_right a_aimmatrix_crouch_idle_aim_pistol_straight_up a_aimmatrix_crouch_idle_aim_pistol_up_center a_aimmatrix_crouch_idle_aim_pistol_mid_center a_aimmatrix_crouch_idle_aim_pistol_down_center a_aimmatrix_crouch_idle_aim_pistol_straight_up a_aimmatrix_crouch_idle_aim_pistol_up_left a_aimmatrix_crouch_idle_aim_pistol_mid_left a_aimmatrix_crouch_idle_aim_pistol_down_left
}
$animation a_aimmatrix_crouch_walk_pistol_straight_up "a_aimmatrix_crouch_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_up_right "a_aimmatrix_crouch_walk_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_mid_right "a_aimmatrix_crouch_walk_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_down_right "a_aimmatrix_crouch_walk_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_straight_up "a_aimmatrix_crouch_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_up_center "a_aimmatrix_crouch_walk_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_mid_center "a_aimmatrix_crouch_walk_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_down_center "a_aimmatrix_crouch_walk_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_straight_up "a_aimmatrix_crouch_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_up_left "a_aimmatrix_crouch_walk_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_mid_left "a_aimmatrix_crouch_walk_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_crouch_walk_pistol_down_left "a_aimmatrix_crouch_walk_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_crouch_walk_pistol "a_aimmatrix_crouch_walk_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_crouch_walk_pistol_straight_up a_aimmatrix_crouch_walk_pistol_up_right a_aimmatrix_crouch_walk_pistol_mid_right a_aimmatrix_crouch_walk_pistol_down_right a_aimmatrix_crouch_walk_pistol_straight_up a_aimmatrix_crouch_walk_pistol_up_center a_aimmatrix_crouch_walk_pistol_mid_center a_aimmatrix_crouch_walk_pistol_down_center a_aimmatrix_crouch_walk_pistol_straight_up a_aimmatrix_crouch_walk_pistol_up_left a_aimmatrix_crouch_walk_pistol_mid_left a_aimmatrix_crouch_walk_pistol_down_left
}
$animation a_aimmatrix_walk_pistol_straight_up "a_aimmatrix_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_up_right "a_aimmatrix_walk_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_mid_right "a_aimmatrix_walk_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_down_right "a_aimmatrix_walk_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_straight_up "a_aimmatrix_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_up_center "a_aimmatrix_walk_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_mid_center "a_aimmatrix_walk_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_down_center "a_aimmatrix_walk_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_straight_up "a_aimmatrix_walk_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_up_left "a_aimmatrix_walk_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_mid_left "a_aimmatrix_walk_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_walk_pistol_down_left "a_aimmatrix_walk_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_walk_pistol "a_aimmatrix_walk_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_walk_pistol_straight_up a_aimmatrix_walk_pistol_up_right a_aimmatrix_walk_pistol_mid_right a_aimmatrix_walk_pistol_down_right a_aimmatrix_walk_pistol_straight_up a_aimmatrix_walk_pistol_up_center a_aimmatrix_walk_pistol_mid_center a_aimmatrix_walk_pistol_down_center a_aimmatrix_walk_pistol_straight_up a_aimmatrix_walk_pistol_up_left a_aimmatrix_walk_pistol_mid_left a_aimmatrix_walk_pistol_down_left
}
$animation a_aimmatrix_run_pistol_straight_up "a_aimmatrix_run_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_up_right "a_aimmatrix_run_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_mid_right "a_aimmatrix_run_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_down_right "a_aimmatrix_run_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_straight_up "a_aimmatrix_run_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_up_center "a_aimmatrix_run_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_mid_center "a_aimmatrix_run_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_down_center "a_aimmatrix_run_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_straight_up "a_aimmatrix_run_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_up_left "a_aimmatrix_run_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_mid_left "a_aimmatrix_run_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_run_pistol_down_left "a_aimmatrix_run_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_run_pistol "a_aimmatrix_run_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_run_pistol_straight_up a_aimmatrix_run_pistol_up_right a_aimmatrix_run_pistol_mid_right a_aimmatrix_run_pistol_down_right a_aimmatrix_run_pistol_straight_up a_aimmatrix_run_pistol_up_center a_aimmatrix_run_pistol_mid_center a_aimmatrix_run_pistol_down_center a_aimmatrix_run_pistol_straight_up a_aimmatrix_run_pistol_up_left a_aimmatrix_run_pistol_mid_left a_aimmatrix_run_pistol_down_left
}
$animation a_aimmatrix_prone_idle_pistol_straight_up "a_aimmatrix_prone_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_up_right "a_aimmatrix_prone_idle_pistol_up_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_mid_right "a_aimmatrix_prone_idle_pistol_mid_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_down_right "a_aimmatrix_prone_idle_pistol_down_right" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_straight_up "a_aimmatrix_prone_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_up_center "a_aimmatrix_prone_idle_pistol_up_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_mid_center "a_aimmatrix_prone_idle_pistol_mid_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_down_center "a_aimmatrix_prone_idle_pistol_down_center" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_straight_up "a_aimmatrix_prone_idle_pistol_straight_up" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_up_left "a_aimmatrix_prone_idle_pistol_up_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_mid_left "a_aimmatrix_prone_idle_pistol_mid_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$animation a_aimmatrix_prone_idle_pistol_down_left "a_aimmatrix_prone_idle_pistol_down_left" fps 30.000000 subtract mdldecompiler_delta.smd 0

$sequence aimmatrix_prone_idle_pistol "a_aimmatrix_prone_idle_pistol_straight_up" fps 30.00 {
  blendwidth 12
  blend body_yaw -50.812321 45.012627
  delta
 a_aimmatrix_prone_idle_pistol_straight_up a_aimmatrix_prone_idle_pistol_up_right a_aimmatrix_prone_idle_pistol_mid_right a_aimmatrix_prone_idle_pistol_down_right a_aimmatrix_prone_idle_pistol_straight_up a_aimmatrix_prone_idle_pistol_up_center a_aimmatrix_prone_idle_pistol_mid_center a_aimmatrix_prone_idle_pistol_down_center a_aimmatrix_prone_idle_pistol_straight_up a_aimmatrix_prone_idle_pistol_up_left a_aimmatrix_prone_idle_pistol_mid_left a_aimmatrix_prone_idle_pistol_down_left
}
$sequence ProneDown_Stand "ProneDown_Stand" ACT_MP_STAND_TO_PRONE 1 fps 30.00
$sequence ProneUp_Stand "ProneUp_Stand" ACT_MP_PRONE_TO_STAND 1 fps 30.00
$sequence ProneDown_Crouch "ProneDown_Crouch" ACT_MP_CROUCH_TO_PRONE 1 fps 30.00
$sequence ProneUp_Crouch "ProneUp_Crouch" ACT_MP_PRONE_TO_CROUCH 1 fps 30.00
$sequence Jump "Jump" ACT_MP_JUMP 1 fps 30.00
$sequence StandIdle_BAR "StandIdle_BAR" loop ACT_DOD_STAND_IDLE_BAR 1 fps 30.00
$sequence CrouchIdle_BAR "CrouchIdle_BAR" loop ACT_DOD_CROUCH_IDLE_BAR 1 fps 30.00
$sequence ProneWalkIdle_BAR "ProneWalkIdle_BAR" loop ACT_DOD_PRONEWALK_IDLE_BAR 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_BAR "pose_blend_walkN_WalkIdle_BAR" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_BAR "a_pose_walkI_WalkIdle_BAR" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_BAR "a_walkSW" loop ACT_DOD_WALK_IDLE_BAR 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_BAR a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_BAR "blend_crouchN_CrouchWalkIdle_BAR" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_BAR "a_crouchI_CrouchWalkIdle_BAR" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_BAR "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_BAR 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_BAR a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_BAR "a_runSW_RunIdle_BAR" loop fps 30.000000
$animation a_runW_RunIdle_BAR "a_runW_RunIdle_BAR" loop fps 30.000000
$animation a_runNW_RunIdle_BAR "a_runNW_RunIdle_BAR" loop fps 30.000000
$animation a_runS_RunIdle_BAR "a_runS_RunIdle_BAR" loop fps 30.000000
$animation a_runI_RunIdle_BAR "a_runI_RunIdle_BAR" loop fps 30.000000
$animation a_runN_RunIdle_BAR "a_runN_RunIdle_BAR" loop fps 30.000000
$animation a_runSE_RunIdle_BAR "a_runSE_RunIdle_BAR" loop fps 30.000000
$animation a_runE_RunIdle_BAR "a_runE_RunIdle_BAR" loop fps 30.000000
$animation a_runNE_RunIdle_BAR "a_runNE_RunIdle_BAR" loop fps 30.000000
$sequence r_RunIdle_BAR "a_runSW_RunIdle_BAR" loop ACT_DOD_RUN_IDLE_BAR 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_BAR a_runW_RunIdle_BAR a_runNW_RunIdle_BAR a_runS_RunIdle_BAR a_runI_RunIdle_BAR a_runN_RunIdle_BAR a_runSE_RunIdle_BAR a_runE_RunIdle_BAR a_runNE_RunIdle_BAR
}
$sequence blend_sprintN_SprintIdle_BAR "blend_sprintN_SprintIdle_BAR" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_BAR "a_sprintI_SprintIdle_BAR" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_BAR "a_runSW" loop ACT_DOD_SPRINT_IDLE_BAR 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_BAR a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_BAR "StandAim_BAR" loop ACT_DOD_STAND_AIM_BAR 1 fps 30.00
$sequence CrouchAim_BAR "CrouchAim_BAR" loop ACT_DOD_CROUCH_AIM_BAR 1 fps 30.00
$sequence ProneAim_BAR "ProneAim_BAR" loop ACT_DOD_PRONE_AIM_BAR 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_BAR "pose_blend_walkN_WalkAim_BAR" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_BAR "a_pose_walkI_WalkAim_BAR" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_BAR "a_walkSW" loop ACT_DOD_WALK_AIM_BAR 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_BAR a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_BAR "pose_blend_crouchN_CrouchWalkAim_BAR" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_BAR "a_pose_crouchI_CrouchWalkAim_BAR" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_BAR "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_BAR 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_BAR a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_BAR "pose_blend_runN_RunAim_BAR" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_BAR "a_pose_runI_RunAim_BAR" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_BAR "a_runSW" loop ACT_DOD_RUN_AIM_BAR 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_BAR a_runN a_runSE a_runE a_runNE
}
$sequence Attack_BAR "Attack_BAR" ACT_DOD_PRIMARYATTACK_BAR 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_BAR "AttackProne_BAR" ACT_DOD_PRIMARYATTACK_PRONE_BAR 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_BAR "Reload_BAR" ACT_DOD_RELOAD_BAR 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_BAR "ReloadCrouch_BAR" ACT_DOD_RELOAD_CROUCH_BAR 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_BAR "ReloadProne_BAR" ACT_DOD_RELOAD_PRONE_BAR 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_RIFLE "StandIdle_RIFLE" loop ACT_DOD_STAND_IDLE_RIFLE 1 fps 30.00
$sequence CrouchIdle_RIFLE "CrouchIdle_RIFLE" loop ACT_DOD_CROUCH_IDLE_RIFLE 1 fps 30.00
$sequence ProneWalkIdle_RIFLE "ProneWalkIdle_RIFLE" loop ACT_DOD_PRONEWALK_IDLE_RIFLE 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_RIFLE "pose_blend_walkN_WalkIdle_RIFLE" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_RIFLE "a_pose_walkI_WalkIdle_RIFLE" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_RIFLE "a_walkSW" loop ACT_DOD_WALK_IDLE_RIFLE 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_RIFLE a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_RIFLE "blend_crouchN_CrouchWalkIdle_RIFLE" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_RIFLE "a_crouchI_CrouchWalkIdle_RIFLE" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_RIFLE "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_RIFLE 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_RIFLE a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_RIFLE "a_runSW_RunIdle_RIFLE" loop fps 30.000000
$animation a_runW_RunIdle_RIFLE "a_runW_RunIdle_RIFLE" loop fps 30.000000
$animation a_runNW_RunIdle_RIFLE "a_runNW_RunIdle_RIFLE" loop fps 30.000000
$animation a_runS_RunIdle_RIFLE "a_runS_RunIdle_RIFLE" loop fps 30.000000
$animation a_runI_RunIdle_RIFLE "a_runI_RunIdle_RIFLE" loop fps 30.000000
$animation a_runN_RunIdle_RIFLE "a_runN_RunIdle_RIFLE" loop fps 30.000000
$animation a_runSE_RunIdle_RIFLE "a_runSE_RunIdle_RIFLE" loop fps 30.000000
$animation a_runE_RunIdle_RIFLE "a_runE_RunIdle_RIFLE" loop fps 30.000000
$animation a_runNE_RunIdle_RIFLE "a_runNE_RunIdle_RIFLE" loop fps 30.000000
$sequence r_RunIdle_RIFLE "a_runSW_RunIdle_RIFLE" loop ACT_DOD_RUN_IDLE_RIFLE 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_RIFLE a_runW_RunIdle_RIFLE a_runNW_RunIdle_RIFLE a_runS_RunIdle_RIFLE a_runI_RunIdle_RIFLE a_runN_RunIdle_RIFLE a_runSE_RunIdle_RIFLE a_runE_RunIdle_RIFLE a_runNE_RunIdle_RIFLE
}
$sequence blend_sprintN_SprintIdle_RIFLE "blend_sprintN_SprintIdle_RIFLE" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_RIFLE "a_sprintI_SprintIdle_RIFLE" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_RIFLE "a_runSW" loop ACT_DOD_SPRINT_IDLE_RIFLE 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_RIFLE a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_RIFLE "StandAim_RIFLE" loop ACT_DOD_STAND_AIM_RIFLE 1 fps 30.00
$sequence CrouchAim_RIFLE "CrouchAim_RIFLE" loop ACT_DOD_CROUCH_AIM_RIFLE 1 fps 30.00
$sequence ProneAim_RIFLE "ProneAim_RIFLE" loop ACT_DOD_PRONE_AIM_RIFLE 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_RIFLE "pose_blend_walkN_WalkAim_RIFLE" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_RIFLE "a_pose_walkI_WalkAim_RIFLE" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_RIFLE "a_walkSW" loop ACT_DOD_WALK_AIM_RIFLE 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_RIFLE a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_RIFLE "pose_blend_crouchN_CrouchWalkAim_RIFLE" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_RIFLE "a_pose_crouchI_CrouchWalkAim_RIFLE" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_RIFLE "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_RIFLE 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_RIFLE a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_RIFLE "pose_blend_runN_RunAim_RIFLE" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_RIFLE "a_pose_runI_RunAim_RIFLE" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_RIFLE "a_runSW" loop ACT_DOD_RUN_AIM_RIFLE 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_RIFLE a_runN a_runSE a_runE a_runNE
}
$sequence Attack_RIFLE "Attack_RIFLE" ACT_DOD_PRIMARYATTACK_RIFLE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_RIFLE "AttackProne_RIFLE" ACT_DOD_PRIMARYATTACK_PRONE_RIFLE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_RIFLE "Reload_RIFLE" ACT_DOD_RELOAD_RIFLE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_RIFLE "ReloadCrouch_RIFLE" ACT_DOD_RELOAD_CROUCH_RIFLE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_RIFLE "ReloadProne_RIFLE" ACT_DOD_RELOAD_PRONE_RIFLE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_M1CARBINE "Reload_M1CARBINE" ACT_DOD_RELOAD_M1CARBINE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_M1CARBINE "ReloadCrouch_M1CARBINE" ACT_DOD_RELOAD_CROUCH_M1CARBINE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_M1CARBINE "ReloadProne_M1CARBINE" ACT_DOD_RELOAD_PRONE_M1CARBINE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_BOLT "StandIdle_BOLT" loop ACT_DOD_STAND_IDLE_BOLT 1 fps 30.00
$sequence CrouchIdle_BOLT "CrouchIdle_BOLT" loop ACT_DOD_CROUCH_IDLE_BOLT 1 fps 30.00
$sequence ProneWalkIdle_BOLT "ProneWalkIdle_BOLT" loop ACT_DOD_PRONEWALK_IDLE_BOLT 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_BOLT "pose_blend_walkN_WalkIdle_BOLT" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_BOLT "a_pose_walkI_WalkIdle_BOLT" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_BOLT "a_walkSW" loop ACT_DOD_WALK_IDLE_BOLT 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_BOLT a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_BOLT "blend_crouchN_CrouchWalkIdle_BOLT" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_BOLT "a_crouchI_CrouchWalkIdle_BOLT" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_BOLT "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_BOLT 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_BOLT a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_BOLT "a_runSW_RunIdle_BOLT" loop fps 30.000000
$animation a_runW_RunIdle_BOLT "a_runW_RunIdle_BOLT" loop fps 30.000000
$animation a_runNW_RunIdle_BOLT "a_runNW_RunIdle_BOLT" loop fps 30.000000
$animation a_runS_RunIdle_BOLT "a_runS_RunIdle_BOLT" loop fps 30.000000
$animation a_runI_RunIdle_BOLT "a_runI_RunIdle_BOLT" loop fps 30.000000
$animation a_runN_RunIdle_BOLT "a_runN_RunIdle_BOLT" loop fps 30.000000
$animation a_runSE_RunIdle_BOLT "a_runSE_RunIdle_BOLT" loop fps 30.000000
$animation a_runE_RunIdle_BOLT "a_runE_RunIdle_BOLT" loop fps 30.000000
$animation a_runNE_RunIdle_BOLT "a_runNE_RunIdle_BOLT" loop fps 30.000000
$sequence r_RunIdle_BOLT "a_runSW_RunIdle_BOLT" loop ACT_DOD_RUN_IDLE_BOLT 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_BOLT a_runW_RunIdle_BOLT a_runNW_RunIdle_BOLT a_runS_RunIdle_BOLT a_runI_RunIdle_BOLT a_runN_RunIdle_BOLT a_runSE_RunIdle_BOLT a_runE_RunIdle_BOLT a_runNE_RunIdle_BOLT
}
$sequence blend_sprintN_SprintIdle_BOLT "blend_sprintN_SprintIdle_BOLT" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_BOLT "a_sprintI_SprintIdle_BOLT" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_BOLT "a_runSW" loop ACT_DOD_SPRINT_IDLE_BOLT 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_BOLT a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_BOLT "StandAim_BOLT" loop ACT_DOD_STAND_AIM_BOLT 1 fps 30.00
$sequence CrouchAim_BOLT "CrouchAim_BOLT" loop ACT_DOD_CROUCH_AIM_BOLT 1 fps 30.00
$sequence ProneAim_BOLT "ProneAim_BOLT" loop ACT_DOD_PRONE_AIM_BOLT 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_BOLT "pose_blend_walkN_WalkAim_BOLT" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_BOLT "a_pose_walkI_WalkAim_BOLT" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_BOLT "a_walkSW" loop ACT_DOD_WALK_AIM_BOLT 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_BOLT a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_BOLT "pose_blend_crouchN_CrouchWalkAim_BOLT" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_BOLT "a_pose_crouchI_CrouchWalkAim_BOLT" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_BOLT "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_BOLT 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_BOLT a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_BOLT "pose_blend_runN_RunAim_BOLT" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_BOLT "a_pose_runI_RunAim_BOLT" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_BOLT "a_runSW" loop ACT_DOD_RUN_AIM_BOLT 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_BOLT a_runN a_runSE a_runE a_runNE
}
$sequence Attack_BOLT "Attack_BOLT" ACT_DOD_PRIMARYATTACK_BOLT 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackProne_BOLT "AttackProne_BOLT" ACT_DOD_PRIMARYATTACK_PRONE_BOLT 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence Reload_BOLT "Reload_BOLT" ACT_DOD_RELOAD_BOLT 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_BOLT "ReloadCrouch_BOLT" ACT_DOD_RELOAD_CROUCH_BOLT 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_BOLT "ReloadProne_BOLT" ACT_DOD_RELOAD_PRONE_BOLT 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_RIFLEGRENADE "Reload_RIFLEGRENADE" ACT_DOD_RELOAD_RIFLEGRENADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_RIFLEGRENADE "ReloadCrouch_RIFLEGRENADE" ACT_DOD_RELOAD_CROUCH_RIFLEGRENADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_RIFLEGRENADE "ReloadProne_RIFLEGRENADE" ACT_DOD_RELOAD_PRONE_RIFLEGRENADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_C96 "StandIdle_C96" loop ACT_DOD_STAND_IDLE_C96 1 fps 30.00
$sequence CrouchIdle_C96 "CrouchIdle_C96" loop ACT_DOD_CROUCH_IDLE_C96 1 fps 30.00
$sequence ProneWalkIdle_C96 "ProneWalkIdle_C96" loop ACT_DOD_PRONEWALK_IDLE_C96 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_C96 "pose_blend_walkN_WalkIdle_C96" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_C96 "a_pose_walkI_WalkIdle_C96" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_C96 "a_walkSW" loop ACT_DOD_WALK_IDLE_C96 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_C96 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_C96 "blend_crouchN_CrouchWalkIdle_C96" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_C96 "a_crouchI_CrouchWalkIdle_C96" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_C96 "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_C96 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_C96 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_C96 "a_runSW_RunIdle_C96" loop fps 30.000000
$animation a_runW_RunIdle_C96 "a_runW_RunIdle_C96" loop fps 30.000000
$animation a_runNW_RunIdle_C96 "a_runNW_RunIdle_C96" loop fps 30.000000
$animation a_runS_RunIdle_C96 "a_runS_RunIdle_C96" loop fps 30.000000
$animation a_runI_RunIdle_C96 "a_runI_RunIdle_C96" loop fps 30.000000
$animation a_runN_RunIdle_C96 "a_runN_RunIdle_C96" loop fps 30.000000
$animation a_runSE_RunIdle_C96 "a_runSE_RunIdle_C96" loop fps 30.000000
$animation a_runE_RunIdle_C96 "a_runE_RunIdle_C96" loop fps 30.000000
$animation a_runNE_RunIdle_C96 "a_runNE_RunIdle_C96" loop fps 30.000000
$sequence r_RunIdle_C96 "a_runSW_RunIdle_C96" loop ACT_DOD_RUN_IDLE_C96 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_C96 a_runW_RunIdle_C96 a_runNW_RunIdle_C96 a_runS_RunIdle_C96 a_runI_RunIdle_C96 a_runN_RunIdle_C96 a_runSE_RunIdle_C96 a_runE_RunIdle_C96 a_runNE_RunIdle_C96
}
$sequence blend_sprintN_SprintIdle_C96 "blend_sprintN_SprintIdle_C96" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_C96 "a_sprintI_SprintIdle_C96" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_C96 "a_runSW" loop ACT_DOD_SPRINT_IDLE_C96 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_C96 a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_C96 "StandAim_C96" loop ACT_DOD_STAND_AIM_C96 1 fps 30.00
$sequence CrouchAim_C96 "CrouchAim_C96" loop ACT_DOD_CROUCH_AIM_C96 1 fps 30.00
$sequence ProneAim_C96 "ProneAim_C96" loop ACT_DOD_PRONE_AIM_C96 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_C96 "pose_blend_walkN_WalkAim_C96" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_C96 "a_pose_walkI_WalkAim_C96" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_C96 "a_walkSW" loop ACT_DOD_WALK_AIM_C96 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_C96 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_C96 "pose_blend_crouchN_CrouchWalkAim_C96" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_C96 "a_pose_crouchI_CrouchWalkAim_C96" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_C96 "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_C96 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_C96 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_C96 "pose_blend_runN_RunAim_C96" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_C96 "a_pose_runI_RunAim_C96" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_C96 "a_runSW" loop ACT_DOD_RUN_AIM_C96 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_C96 a_runN a_runSE a_runE a_runNE
}
$sequence Attack_C96 "Attack_C96" ACT_DOD_PRIMARYATTACK_C96 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_C96 "AttackProne_C96" ACT_DOD_PRIMARYATTACK_PRONE_C96 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_C96 "Reload_C96" ACT_DOD_RELOAD_C96 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_C96 "ReloadCrouch_C96" ACT_DOD_RELOAD_CROUCH_C96 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_C96 "ReloadProne_C96" ACT_DOD_RELOAD_PRONE_C96 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_MP44 "StandIdle_MP44" loop ACT_DOD_STAND_IDLE_MP44 1 fps 30.00
$sequence CrouchIdle_MP44 "CrouchIdle_MP44" loop ACT_DOD_CROUCH_IDLE_MP44 1 fps 30.00
$sequence ProneWalkIdle_MP44 "ProneWalkIdle_MP44" loop ACT_DOD_PRONEWALK_IDLE_MP44 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_MP44 "pose_blend_walkN_WalkIdle_MP44" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_MP44 "a_pose_walkI_WalkIdle_MP44" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_MP44 "a_walkSW" loop ACT_DOD_WALK_IDLE_MP44 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_MP44 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_MP44 "blend_crouchN_CrouchWalkIdle_MP44" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_MP44 "a_crouchI_CrouchWalkIdle_MP44" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_MP44 "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_MP44 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_MP44 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_MP44 "a_runSW_RunIdle_MP44" loop fps 30.000000
$animation a_runW_RunIdle_MP44 "a_runW_RunIdle_MP44" loop fps 30.000000
$animation a_runNW_RunIdle_MP44 "a_runNW_RunIdle_MP44" loop fps 30.000000
$animation a_runS_RunIdle_MP44 "a_runS_RunIdle_MP44" loop fps 30.000000
$animation a_runI_RunIdle_MP44 "a_runI_RunIdle_MP44" loop fps 30.000000
$animation a_runN_RunIdle_MP44 "a_runN_RunIdle_MP44" loop fps 30.000000
$animation a_runSE_RunIdle_MP44 "a_runSE_RunIdle_MP44" loop fps 30.000000
$animation a_runE_RunIdle_MP44 "a_runE_RunIdle_MP44" loop fps 30.000000
$animation a_runNE_RunIdle_MP44 "a_runNE_RunIdle_MP44" loop fps 30.000000
$sequence r_RunIdle_MP44 "a_runSW_RunIdle_MP44" loop ACT_DOD_RUN_IDLE_MP44 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_MP44 a_runW_RunIdle_MP44 a_runNW_RunIdle_MP44 a_runS_RunIdle_MP44 a_runI_RunIdle_MP44 a_runN_RunIdle_MP44 a_runSE_RunIdle_MP44 a_runE_RunIdle_MP44 a_runNE_RunIdle_MP44
}
$sequence blend_sprintN_SprintIdle_MP44 "blend_sprintN_SprintIdle_MP44" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_MP44 "a_sprintI_SprintIdle_MP44" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_MP44 "a_runSW" loop ACT_DOD_SPRINT_IDLE_MP44 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_MP44 a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_MP44 "StandAim_MP44" loop ACT_DOD_STAND_AIM_MP44 1 fps 30.00
$sequence CrouchAim_MP44 "CrouchAim_MP44" loop ACT_DOD_CROUCH_AIM_MP44 1 fps 30.00
$sequence ProneAim_MP44 "ProneAim_MP44" loop ACT_DOD_PRONE_AIM_MP44 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_MP44 "pose_blend_walkN_WalkAim_MP44" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_MP44 "a_pose_walkI_WalkAim_MP44" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_MP44 "a_walkSW" loop ACT_DOD_WALK_AIM_MP44 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_MP44 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_MP44 "pose_blend_crouchN_CrouchWalkAim_MP44" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_MP44 "a_pose_crouchI_CrouchWalkAim_MP44" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_MP44 "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_MP44 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_MP44 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_MP44 "pose_blend_runN_RunAim_MP44" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_MP44 "a_pose_runI_RunAim_MP44" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_MP44 "a_runSW" loop ACT_DOD_RUN_AIM_MP44 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_MP44 a_runN a_runSE a_runE a_runNE
}
$sequence Attack_MP44 "Attack_MP44" ACT_DOD_PRIMARYATTACK_MP44 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_MP44 "AttackProne_MP44" ACT_DOD_PRIMARYATTACK_PRONE_MP44 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_MP44 "Reload_MP44" ACT_DOD_RELOAD_MP44 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_MP44 "ReloadCrouch_MP44" ACT_DOD_RELOAD_CROUCH_MP44 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_MP44 "ReloadProne_MP44" ACT_DOD_RELOAD_PRONE_MP44 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_MP40 "StandIdle_MP40" loop ACT_DOD_STAND_IDLE_MP40 1 fps 30.00
$sequence CrouchIdle_MP40 "CrouchIdle_MP40" loop ACT_DOD_CROUCH_IDLE_MP40 1 fps 30.00
$sequence ProneWalkIdle_MP40 "ProneWalkIdle_MP40" loop ACT_DOD_PRONEWALK_IDLE_MP40 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_MP40 "pose_blend_walkN_WalkIdle_MP40" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_MP40 "a_pose_walkI_WalkIdle_MP40" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_MP40 "a_walkSW" loop ACT_DOD_WALK_IDLE_MP40 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_MP40 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_MP40 "blend_crouchN_CrouchWalkIdle_MP40" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_MP40 "a_crouchI_CrouchWalkIdle_MP40" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_MP40 "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_MP40 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_MP40 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_MP40 "a_runSW_RunIdle_MP40" loop fps 30.000000
$animation a_runW_RunIdle_MP40 "a_runW_RunIdle_MP40" loop fps 30.000000
$animation a_runNW_RunIdle_MP40 "a_runNW_RunIdle_MP40" loop fps 30.000000
$animation a_runS_RunIdle_MP40 "a_runS_RunIdle_MP40" loop fps 30.000000
$animation a_runI_RunIdle_MP40 "a_runI_RunIdle_MP40" loop fps 30.000000
$animation a_runN_RunIdle_MP40 "a_runN_RunIdle_MP40" loop fps 30.000000
$animation a_runSE_RunIdle_MP40 "a_runSE_RunIdle_MP40" loop fps 30.000000
$animation a_runE_RunIdle_MP40 "a_runE_RunIdle_MP40" loop fps 30.000000
$animation a_runNE_RunIdle_MP40 "a_runNE_RunIdle_MP40" loop fps 30.000000
$sequence r_RunIdle_MP40 "a_runSW_RunIdle_MP40" loop ACT_DOD_RUN_IDLE_MP40 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_MP40 a_runW_RunIdle_MP40 a_runNW_RunIdle_MP40 a_runS_RunIdle_MP40 a_runI_RunIdle_MP40 a_runN_RunIdle_MP40 a_runSE_RunIdle_MP40 a_runE_RunIdle_MP40 a_runNE_RunIdle_MP40
}
$sequence blend_sprintN_SprintIdle_MP40 "blend_sprintN_SprintIdle_MP40" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_MP40 "a_sprintI_SprintIdle_MP40" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_MP40 "a_runSW" loop ACT_DOD_SPRINT_IDLE_MP40 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_MP40 a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_MP40 "StandAim_MP40" loop ACT_DOD_STAND_AIM_MP40 1 fps 30.00
$sequence CrouchAim_MP40 "CrouchAim_MP40" loop ACT_DOD_CROUCH_AIM_MP40 1 fps 30.00
$sequence ProneAim_MP40 "ProneAim_MP40" loop ACT_DOD_PRONE_AIM_MP40 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_MP40 "pose_blend_walkN_WalkAim_MP40" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_MP40 "a_pose_walkI_WalkAim_MP40" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_MP40 "a_walkSW" loop ACT_DOD_WALK_AIM_MP40 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_MP40 a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_MP40 "pose_blend_crouchN_CrouchWalkAim_MP40" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_MP40 "a_pose_crouchI_CrouchWalkAim_MP40" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_MP40 "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_MP40 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_MP40 a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_MP40 "pose_blend_runN_RunAim_MP40" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_MP40 "a_pose_runI_RunAim_MP40" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_MP40 "a_runSW" loop ACT_DOD_RUN_AIM_MP40 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_MP40 a_runN a_runSE a_runE a_runNE
}
$sequence Attack_MP40 "Attack_MP40" ACT_DOD_PRIMARYATTACK_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_MP40 "AttackProne_MP40" ACT_DOD_PRIMARYATTACK_PRONE_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_MP40 "Reload_MP40" ACT_DOD_RELOAD_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_MP40 "ReloadCrouch_MP40" ACT_DOD_RELOAD_CROUCH_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_MP40 "ReloadProne_MP40" ACT_DOD_RELOAD_PRONE_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttack_MP40 "SecondaryAttack_MP40" ACT_DOD_SECONDARYATTACK_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttackCrouch_MP40 "SecondaryAttackCrouch_MP40" ACT_DOD_SECONDARYATTACK_CROUCH_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttackProne_MP40 "SecondaryAttackProne_MP40" ACT_DOD_SECONDARYATTACK_PRONE_MP40 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_TOMMY "StandIdle_TOMMY" loop ACT_DOD_STAND_IDLE_TOMMY 1 fps 30.00
$sequence CrouchIdle_TOMMY "CrouchIdle_TOMMY" loop ACT_DOD_CROUCH_IDLE_TOMMY 1 fps 30.00
$sequence ProneWalkIdle_TOMMY "ProneWalkIdle_TOMMY" loop ACT_DOD_PRONEWALK_IDLE_TOMMY 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_TOMMY "pose_blend_walkN_WalkIdle_TOMMY" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_TOMMY "a_pose_walkI_WalkIdle_TOMMY" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_TOMMY "a_walkSW" loop ACT_DOD_WALK_IDLE_TOMMY 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_TOMMY a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_TOMMY "blend_crouchN_CrouchWalkIdle_TOMMY" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_TOMMY "a_crouchI_CrouchWalkIdle_TOMMY" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_TOMMY "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_TOMMY 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_TOMMY a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_TOMMY "a_runSW_RunIdle_TOMMY" loop fps 30.000000
$animation a_runW_RunIdle_TOMMY "a_runW_RunIdle_TOMMY" loop fps 30.000000
$animation a_runNW_RunIdle_TOMMY "a_runNW_RunIdle_TOMMY" loop fps 30.000000
$animation a_runS_RunIdle_TOMMY "a_runS_RunIdle_TOMMY" loop fps 30.000000
$animation a_runI_RunIdle_TOMMY "a_runI_RunIdle_TOMMY" loop fps 30.000000
$animation a_runN_RunIdle_TOMMY "a_runN_RunIdle_TOMMY" loop fps 30.000000
$animation a_runSE_RunIdle_TOMMY "a_runSE_RunIdle_TOMMY" loop fps 30.000000
$animation a_runE_RunIdle_TOMMY "a_runE_RunIdle_TOMMY" loop fps 30.000000
$animation a_runNE_RunIdle_TOMMY "a_runNE_RunIdle_TOMMY" loop fps 30.000000
$sequence r_RunIdle_TOMMY "a_runSW_RunIdle_TOMMY" loop ACT_DOD_RUN_IDLE_TOMMY 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_TOMMY a_runW_RunIdle_TOMMY a_runNW_RunIdle_TOMMY a_runS_RunIdle_TOMMY a_runI_RunIdle_TOMMY a_runN_RunIdle_TOMMY a_runSE_RunIdle_TOMMY a_runE_RunIdle_TOMMY a_runNE_RunIdle_TOMMY
}
$sequence blend_sprintN_SprintIdle_TOMMY "blend_sprintN_SprintIdle_TOMMY" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_TOMMY "a_sprintI_SprintIdle_TOMMY" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_TOMMY "a_runSW" loop ACT_DOD_SPRINT_IDLE_TOMMY 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_TOMMY a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_TOMMY "StandAim_TOMMY" loop ACT_DOD_STAND_AIM_TOMMY 1 fps 30.00
$sequence CrouchAim_TOMMY "CrouchAim_TOMMY" loop ACT_DOD_CROUCH_AIM_TOMMY 1 fps 30.00
$sequence ProneAim_TOMMY "ProneAim_TOMMY" loop ACT_DOD_PRONE_AIM_TOMMY 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_TOMMY "pose_blend_walkN_WalkAim_TOMMY" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_TOMMY "a_pose_walkI_WalkAim_TOMMY" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_TOMMY "a_walkSW" loop ACT_DOD_WALK_AIM_TOMMY 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_TOMMY a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_TOMMY "pose_blend_crouchN_CrouchWalkAim_TOMMY" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_TOMMY "a_pose_crouchI_CrouchWalkAim_TOMMY" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_TOMMY "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_TOMMY 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_TOMMY a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_TOMMY "pose_blend_runN_RunAim_TOMMY" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_TOMMY "a_pose_runI_RunAim_TOMMY" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_TOMMY "a_runSW" loop ACT_DOD_RUN_AIM_TOMMY 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_TOMMY a_runN a_runSE a_runE a_runNE
}
$sequence Attack_TOMMY "Attack_TOMMY" ACT_DOD_PRIMARYATTACK_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_TOMMY "AttackProne_TOMMY" ACT_DOD_PRIMARYATTACK_PRONE_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_TOMMY "Reload_TOMMY" ACT_DOD_RELOAD_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_TOMMY "ReloadCrouch_TOMMY" ACT_DOD_RELOAD_CROUCH_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_TOMMY "ReloadProne_TOMMY" ACT_DOD_RELOAD_PRONE_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttack_TOMMY "SecondaryAttack_TOMMY" ACT_DOD_SECONDARYATTACK_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttackCrouch_TOMMY "SecondaryAttackCrouch_TOMMY" ACT_DOD_SECONDARYATTACK_CROUCH_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence SecondaryAttackProne_TOMMY "SecondaryAttackProne_TOMMY" ACT_DOD_SECONDARYATTACK_PRONE_TOMMY 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_MG "StandIdle_MG" loop ACT_DOD_STAND_IDLE_MG 1 fps 30.00
$sequence CrouchIdle_MG "CrouchIdle_MG" loop ACT_DOD_CROUCH_IDLE_MG 1 fps 30.00
$sequence ProneWalkIdle_MG "ProneWalkIdle_MG" loop ACT_DOD_PRONEWALK_IDLE_MG 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_MG "pose_blend_walkN_WalkIdle_MG" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_MG "a_pose_walkI_WalkIdle_MG" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_MG "a_walkSW" loop ACT_DOD_WALK_IDLE_MG 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_MG a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_MG "blend_crouchN_CrouchWalkIdle_MG" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_MG "a_crouchI_CrouchWalkIdle_MG" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_MG "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_MG 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_MG a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_MG "a_runSW_RunIdle_MG" loop fps 30.000000
$animation a_runW_RunIdle_MG "a_runW_RunIdle_MG" loop fps 30.000000
$animation a_runNW_RunIdle_MG "a_runNW_RunIdle_MG" loop fps 30.000000
$animation a_runS_RunIdle_MG "a_runS_RunIdle_MG" loop fps 30.000000
$animation a_runI_RunIdle_MG "a_runI_RunIdle_MG" loop fps 30.000000
$animation a_runN_RunIdle_MG "a_runN_RunIdle_MG" loop fps 30.000000
$animation a_runSE_RunIdle_MG "a_runSE_RunIdle_MG" loop fps 30.000000
$animation a_runE_RunIdle_MG "a_runE_RunIdle_MG" loop fps 30.000000
$animation a_runNE_RunIdle_MG "a_runNE_RunIdle_MG" loop fps 30.000000
$sequence r_RunIdle_MG "a_runSW_RunIdle_MG" loop ACT_DOD_RUN_IDLE_MG 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_MG a_runW_RunIdle_MG a_runNW_RunIdle_MG a_runS_RunIdle_MG a_runI_RunIdle_MG a_runN_RunIdle_MG a_runSE_RunIdle_MG a_runE_RunIdle_MG a_runNE_RunIdle_MG
}
$sequence blend_sprintN_SprintIdle_MG "blend_sprintN_SprintIdle_MG" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_MG "a_sprintI_SprintIdle_MG" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_MG "a_runSW" loop ACT_DOD_SPRINT_IDLE_MG 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_MG a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_MG "StandAim_MG" loop ACT_DOD_STAND_AIM_MG 1 fps 30.00
$sequence CrouchAim_MG "CrouchAim_MG" loop ACT_DOD_CROUCH_AIM_MG 1 fps 30.00
$sequence ProneAim_MG "ProneAim_MG" loop ACT_DOD_PRONE_AIM_MG 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_MG "pose_blend_walkN_WalkAim_MG" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_MG "a_pose_walkI_WalkAim_MG" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_MG "a_walkSW" loop ACT_DOD_WALK_AIM_MG 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_MG a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_MG "pose_blend_crouchN_CrouchWalkAim_MG" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_MG "a_pose_crouchI_CrouchWalkAim_MG" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_MG "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_MG 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_MG a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_MG "pose_blend_runN_RunAim_MG" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_MG "a_pose_runI_RunAim_MG" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_MG "a_runSW" loop ACT_DOD_RUN_AIM_MG 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_MG a_runN a_runSE a_runE a_runNE
}
$sequence Attack_MG "Attack_MG" ACT_DOD_PRIMARYATTACK_MG 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_MG "AttackProne_MG" ACT_DOD_PRIMARYATTACK_PRONE_MG 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_MG "Reload_MG" ACT_DOD_RELOAD_MG 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_MG "ReloadCrouch_MG" ACT_DOD_RELOAD_CROUCH_MG 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_MG "ReloadProne_MG" ACT_DOD_RELOAD_PRONE_MG 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_30CAL "StandIdle_30CAL" loop ACT_DOD_STAND_IDLE_30CAL 1 fps 30.00
$sequence CrouchIdle_30CAL "CrouchIdle_30CAL" loop ACT_DOD_CROUCH_IDLE_30CAL 1 fps 30.00
$sequence ProneWalkIdle_30CAL "ProneWalkIdle_30CAL" loop ACT_DOD_PRONEWALK_IDLE_30CAL 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_30CAL "pose_blend_walkN_WalkIdle_30CAL" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_30CAL "a_pose_walkI_WalkIdle_30CAL" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_30CAL "a_walkSW" loop ACT_DOD_WALK_IDLE_30CAL 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_30CAL a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_30CAL "blend_crouchN_CrouchWalkIdle_30CAL" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_30CAL "a_crouchI_CrouchWalkIdle_30CAL" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_30CAL "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_30CAL 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_30CAL a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_30CAL "a_runSW_RunIdle_30CAL" loop fps 30.000000
$animation a_runW_RunIdle_30CAL "a_runW_RunIdle_30CAL" loop fps 30.000000
$animation a_runNW_RunIdle_30CAL "a_runNW_RunIdle_30CAL" loop fps 30.000000
$animation a_runS_RunIdle_30CAL "a_runS_RunIdle_30CAL" loop fps 30.000000
$animation a_runI_RunIdle_30CAL "a_runI_RunIdle_30CAL" loop fps 30.000000
$animation a_runN_RunIdle_30CAL "a_runN_RunIdle_30CAL" loop fps 30.000000
$animation a_runSE_RunIdle_30CAL "a_runSE_RunIdle_30CAL" loop fps 30.000000
$animation a_runE_RunIdle_30CAL "a_runE_RunIdle_30CAL" loop fps 30.000000
$animation a_runNE_RunIdle_30CAL "a_runNE_RunIdle_30CAL" loop fps 30.000000
$sequence r_RunIdle_30CAL "a_runSW_RunIdle_30CAL" loop ACT_DOD_RUN_IDLE_30CAL 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_30CAL a_runW_RunIdle_30CAL a_runNW_RunIdle_30CAL a_runS_RunIdle_30CAL a_runI_RunIdle_30CAL a_runN_RunIdle_30CAL a_runSE_RunIdle_30CAL a_runE_RunIdle_30CAL a_runNE_RunIdle_30CAL
}
$sequence blend_sprintN_SprintIdle_30CAL "blend_sprintN_SprintIdle_30CAL" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_30CAL "a_sprintI_SprintIdle_30CAL" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_30CAL "a_runSW" loop ACT_DOD_SPRINT_IDLE_30CAL 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_30CAL a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_30CAL "StandAim_30CAL" loop ACT_DOD_STAND_AIM_30CAL 1 fps 30.00
$sequence CrouchAim_30CAL "CrouchAim_30CAL" loop ACT_DOD_CROUCH_AIM_30CAL 1 fps 30.00
$sequence ProneAim_30CAL "ProneAim_30CAL" loop ACT_DOD_PRONE_AIM_30CAL 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_30CAL "pose_blend_walkN_WalkAim_30CAL" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_30CAL "a_pose_walkI_WalkAim_30CAL" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_30CAL "a_walkSW" loop ACT_DOD_WALK_AIM_30CAL 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_30CAL a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_30CAL "pose_blend_crouchN_CrouchWalkAim_30CAL" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_30CAL "a_pose_crouchI_CrouchWalkAim_30CAL" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_30CAL "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_30CAL 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_30CAL a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_30CAL "pose_blend_runN_RunAim_30CAL" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_30CAL "a_pose_runI_RunAim_30CAL" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_30CAL "a_runSW" loop ACT_DOD_RUN_AIM_30CAL 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_30CAL a_runN a_runSE a_runE a_runNE
}
$sequence Attack_30CAL "Attack_30CAL" ACT_DOD_PRIMARYATTACK_30CAL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_30CAL "AttackProne_30CAL" ACT_DOD_PRIMARYATTACK_PRONE_30CAL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_30CAL "Reload_30CAL" ACT_DOD_RELOAD_30CAL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_30CAL "ReloadCrouch_30CAL" ACT_DOD_RELOAD_CROUCH_30CAL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_30CAL "ReloadProne_30CAL" ACT_DOD_RELOAD_PRONE_30CAL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_PISTOL "StandIdle_PISTOL" loop ACT_DOD_STAND_IDLE_PISTOL 1 fps 30.00
$sequence CrouchIdle_PISTOL "CrouchIdle_PISTOL" loop ACT_DOD_CROUCH_IDLE_PISTOL 1 fps 30.00
$sequence ProneWalkIdle_PISTOL "ProneWalkIdle_PISTOL" loop ACT_DOD_PRONEWALK_IDLE_PISTOL 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_PISTOL "pose_blend_walkN_WalkIdle_PISTOL" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_PISTOL "a_pose_walkI_WalkIdle_PISTOL" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_PISTOL "a_walkSW" loop ACT_DOD_WALK_IDLE_PISTOL 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_PISTOL a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_PISTOL "blend_crouchN_CrouchWalkIdle_PISTOL" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_PISTOL "a_crouchI_CrouchWalkIdle_PISTOL" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_PISTOL "a_crouchSW" loop ACT_DOD_CROUCHWALK_IDLE_PISTOL 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_PISTOL a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_PISTOL "a_runSW_RunIdle_PISTOL" loop fps 30.000000
$animation a_runW_RunIdle_PISTOL "a_runW_RunIdle_PISTOL" loop fps 30.000000
$animation a_runNW_RunIdle_PISTOL "a_runNW_RunIdle_PISTOL" loop fps 30.000000
$animation a_runS_RunIdle_PISTOL "a_runS_RunIdle_PISTOL" loop fps 30.000000
$animation a_runI_RunIdle_PISTOL "a_runI_RunIdle_PISTOL" loop fps 30.000000
$animation a_runN_RunIdle_PISTOL "a_runN_RunIdle_PISTOL" loop fps 30.000000
$animation a_runSE_RunIdle_PISTOL "a_runSE_RunIdle_PISTOL" loop fps 30.000000
$animation a_runE_RunIdle_PISTOL "a_runE_RunIdle_PISTOL" loop fps 30.000000
$animation a_runNE_RunIdle_PISTOL "a_runNE_RunIdle_PISTOL" loop fps 30.000000
$sequence r_RunIdle_PISTOL "a_runSW_RunIdle_PISTOL" loop ACT_DOD_RUN_IDLE_PISTOL 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_PISTOL a_runW_RunIdle_PISTOL a_runNW_RunIdle_PISTOL a_runS_RunIdle_PISTOL a_runI_RunIdle_PISTOL a_runN_RunIdle_PISTOL a_runSE_RunIdle_PISTOL a_runE_RunIdle_PISTOL a_runNE_RunIdle_PISTOL
}
$sequence blend_sprintN_SprintIdle_PISTOL "blend_sprintN_SprintIdle_PISTOL" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintIdle_PISTOL "a_sprintI_SprintIdle_PISTOL" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintIdle_PISTOL "a_runSW" loop ACT_DOD_SPRINT_IDLE_PISTOL 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintIdle_PISTOL a_sprintN a_runSW a_runE a_sprintNE
}
$sequence StandAim_PISTOL "StandAim_PISTOL" loop ACT_DOD_STAND_AIM_PISTOL 1 fps 30.00
$sequence CrouchAim_PISTOL "CrouchAim_PISTOL" loop ACT_DOD_CROUCH_AIM_PISTOL 1 fps 30.00
$sequence ProneAim_PISTOL "ProneAim_PISTOL" loop ACT_DOD_PRONE_AIM_PISTOL 1 fps 30.00
$sequence pose_blend_walkN_WalkAim_PISTOL "pose_blend_walkN_WalkAim_PISTOL" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkAim_PISTOL "a_pose_walkI_WalkAim_PISTOL" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkAim_PISTOL "a_walkSW" loop ACT_DOD_WALK_AIM_PISTOL 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkAim_PISTOL a_walkN a_walkSE a_walkE a_walkNE
}
$sequence pose_blend_crouchN_CrouchWalkAim_PISTOL "pose_blend_crouchN_CrouchWalkAim_PISTOL" fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_pose_crouchI_CrouchWalkAim_PISTOL "a_pose_crouchI_CrouchWalkAim_PISTOL" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence cw_CrouchWalkAim_PISTOL "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_PISTOL 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_pose_crouchI_CrouchWalkAim_PISTOL a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$sequence pose_blend_runN_RunAim_PISTOL "pose_blend_runN_RunAim_PISTOL" fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_runNW "a_runNW" loop fps 33.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_pose_runI_RunAim_PISTOL "a_pose_runI_RunAim_PISTOL" loop fps 33.000000
$animation a_runN "a_runN" loop fps 33.000000
$animation a_runSE "a_runSE" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_runNE "a_runNE" loop fps 33.000000
$sequence r_RunAim_PISTOL "a_runSW" loop ACT_DOD_RUN_AIM_PISTOL 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_runNW a_runS a_pose_runI_RunAim_PISTOL a_runN a_runSE a_runE a_runNE
}
$sequence Attack_PISTOL "Attack_PISTOL" ACT_DOD_PRIMARYATTACK_PISTOL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence AttackProne_PISTOL "AttackProne_PISTOL" ACT_DOD_PRIMARYATTACK_PRONE_PISTOL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence Reload_PISTOL "Reload_PISTOL" ACT_DOD_RELOAD_PISTOL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadCrouch_PISTOL "ReloadCrouch_PISTOL" ACT_DOD_RELOAD_CROUCH_PISTOL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence ReloadProne_PISTOL "ReloadProne_PISTOL" ACT_DOD_RELOAD_PRONE_PISTOL 1 fps 30.00 subtract mdldecompiler_delta.smd 0
$sequence StandIdle_GREN_STICK "StandIdle_GREN_STICK" loop ACT_DOD_STAND_AIM_GREN_STICK 1 fps 30.00
$sequence CrouchIdle_GREN_STICK "CrouchIdle_GREN_STICK" loop ACT_DOD_CROUCH_AIM_GREN_STICK 1 fps 30.00
$sequence ProneAim_GREN_STICK "ProneAim_GREN_STICK" loop ACT_DOD_PRONE_AIM_GREN_STICK 1 fps 30.00
$sequence ProneWalkAim_GREN_STICK "ProneWalkAim_GREN_STICK" loop ACT_DOD_PRONEWALK_AIM_GREN_STICK 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_GREN_STICK "pose_blend_walkN_WalkIdle_GREN_STICK" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_GREN_STICK "a_pose_walkI_WalkIdle_GREN_STICK" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_GREN_STICK "a_walkSW" loop ACT_DOD_WALK_AIM_GREN_STICK 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_GREN_STICK a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_GREN_STICK "blend_crouchN_CrouchWalkIdle_GREN_STICK" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_GREN_STICK "a_crouchI_CrouchWalkIdle_GREN_STICK" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_GREN_STICK "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_GREN_STICK 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_GREN_STICK a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_GREN_STICK "a_runSW_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runW_RunIdle_GREN_STICK "a_runW_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runNW_RunIdle_GREN_STICK "a_runNW_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runS_RunIdle_GREN_STICK "a_runS_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runI_RunIdle_GREN_STICK "a_runI_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runN_RunIdle_GREN_STICK "a_runN_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runSE_RunIdle_GREN_STICK "a_runSE_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runE_RunIdle_GREN_STICK "a_runE_RunIdle_GREN_STICK" loop fps 30.000000
$animation a_runNE_RunIdle_GREN_STICK "a_runNE_RunIdle_GREN_STICK" loop fps 30.000000
$sequence r_RunIdle_GREN_STICK "a_runSW_RunIdle_GREN_STICK" loop ACT_DOD_RUN_AIM_GREN_STICK 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_GREN_STICK a_runW_RunIdle_GREN_STICK a_runNW_RunIdle_GREN_STICK a_runS_RunIdle_GREN_STICK a_runI_RunIdle_GREN_STICK a_runN_RunIdle_GREN_STICK a_runSE_RunIdle_GREN_STICK a_runE_RunIdle_GREN_STICK a_runNE_RunIdle_GREN_STICK
}
$sequence blend_sprintN_SprintAim_GREN_STICK "blend_sprintN_SprintAim_GREN_STICK" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintAim_GREN_STICK "a_sprintI_SprintAim_GREN_STICK" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintAim_GREN_STICK "a_runSW" loop ACT_DOD_SPRINT_AIM_GREN_STICK 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintAim_GREN_STICK a_sprintN a_runSW a_runE a_sprintNE
}
$sequence Attack_GREN_STICK "Attack_GREN_STICK" ACT_DOD_PRIMARYATTACK_GREN_STICK 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackCrouch_GREN_STICK "AttackCrouch_GREN_STICK" ACT_DOD_PRIMARYATTACK_CROUCH_GREN_STICK 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackProne_GREN_STICK "AttackProne_GREN_STICK" ACT_DOD_PRIMARYATTACK_PRONE_GREN_STICK 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence StandIdle_GREN_FRAG "StandIdle_GREN_FRAG" loop ACT_DOD_STAND_AIM_GREN_FRAG 1 fps 30.00
$sequence CrouchIdle_GREN_FRAG "CrouchIdle_GREN_FRAG" loop ACT_DOD_CROUCH_AIM_GREN_FRAG 1 fps 30.00
$sequence ProneAim_GREN_FRAG "ProneAim_GREN_FRAG" loop ACT_DOD_PRONE_AIM_GREN_FRAG 1 fps 30.00
$sequence ProneWalkAim_GREN_FRAG "ProneWalkAim_GREN_FRAG" loop ACT_DOD_PRONEWALK_AIM_GREN_FRAG 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_GREN_FRAG "pose_blend_walkN_WalkIdle_GREN_FRAG" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_GREN_FRAG "a_pose_walkI_WalkIdle_GREN_FRAG" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_GREN_FRAG "a_walkSW" loop ACT_DOD_WALK_AIM_GREN_FRAG 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_GREN_FRAG a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_GREN_FRAG "blend_crouchN_CrouchWalkIdle_GREN_FRAG" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_GREN_FRAG "a_crouchI_CrouchWalkIdle_GREN_FRAG" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_GREN_FRAG "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_GREN_FRAG 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_GREN_FRAG a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_GREN_FRAG "a_runSW_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runW_RunIdle_GREN_FRAG "a_runW_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runNW_RunIdle_GREN_FRAG "a_runNW_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runS_RunIdle_GREN_FRAG "a_runS_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runI_RunIdle_GREN_FRAG "a_runI_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runN_RunIdle_GREN_FRAG "a_runN_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runSE_RunIdle_GREN_FRAG "a_runSE_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runE_RunIdle_GREN_FRAG "a_runE_RunIdle_GREN_FRAG" loop fps 30.000000
$animation a_runNE_RunIdle_GREN_FRAG "a_runNE_RunIdle_GREN_FRAG" loop fps 30.000000
$sequence r_RunIdle_GREN_FRAG "a_runSW_RunIdle_GREN_FRAG" loop ACT_DOD_RUN_AIM_GREN_FRAG 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_GREN_FRAG a_runW_RunIdle_GREN_FRAG a_runNW_RunIdle_GREN_FRAG a_runS_RunIdle_GREN_FRAG a_runI_RunIdle_GREN_FRAG a_runN_RunIdle_GREN_FRAG a_runSE_RunIdle_GREN_FRAG a_runE_RunIdle_GREN_FRAG a_runNE_RunIdle_GREN_FRAG
}
$sequence blend_sprintN_SprintAim_GREN_FRAG "blend_sprintN_SprintAim_GREN_FRAG" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintAim_GREN_FRAG "a_sprintI_SprintAim_GREN_FRAG" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintAim_GREN_FRAG "a_runSW" loop ACT_DOD_SPRINT_AIM_GREN_FRAG 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintAim_GREN_FRAG a_sprintN a_runSW a_runE a_sprintNE
}
$sequence Attack_GREN_FRAG "Attack_GREN_FRAG" ACT_DOD_PRIMARYATTACK_GREN_FRAG 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackCrouch_GREN_FRAG "AttackCrouch_GREN_FRAG" ACT_DOD_PRIMARYATTACK_CROUCH_GREN_FRAG 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackProne_GREN_FRAG "AttackProne_GREN_FRAG" ACT_DOD_PRIMARYATTACK_PRONE_GREN_FRAG 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence StandIdle_KNIFE "StandIdle_KNIFE" loop ACT_DOD_STAND_AIM_KNIFE 1 fps 30.00
$sequence CrouchIdle_KNIFE "CrouchIdle_KNIFE" loop ACT_DOD_CROUCH_AIM_KNIFE 1 fps 30.00
$sequence ProneAim_KNIFE "ProneAim_KNIFE" loop ACT_DOD_PRONE_AIM_KNIFE 1 fps 30.00
$sequence ProneWalkAim_KNIFE "ProneWalkAim_KNIFE" loop ACT_DOD_PRONEWALK_AIM_KNIFE 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_KNIFE "pose_blend_walkN_WalkIdle_KNIFE" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_KNIFE "a_pose_walkI_WalkIdle_KNIFE" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_KNIFE "a_walkSW" loop ACT_DOD_WALK_AIM_KNIFE 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_KNIFE a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_KNIFE "blend_crouchN_CrouchWalkIdle_KNIFE" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_KNIFE "a_crouchI_CrouchWalkIdle_KNIFE" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_KNIFE "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_KNIFE 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_KNIFE a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_KNIFE "a_runSW_RunIdle_KNIFE" loop fps 30.000000
$animation a_runW_RunIdle_KNIFE "a_runW_RunIdle_KNIFE" loop fps 30.000000
$animation a_runNW_RunIdle_KNIFE "a_runNW_RunIdle_KNIFE" loop fps 30.000000
$animation a_runS_RunIdle_KNIFE "a_runS_RunIdle_KNIFE" loop fps 30.000000
$animation a_runI_RunIdle_KNIFE "a_runI_RunIdle_KNIFE" loop fps 30.000000
$animation a_runN_RunIdle_KNIFE "a_runN_RunIdle_KNIFE" loop fps 30.000000
$animation a_runSE_RunIdle_KNIFE "a_runSE_RunIdle_KNIFE" loop fps 30.000000
$animation a_runE_RunIdle_KNIFE "a_runE_RunIdle_KNIFE" loop fps 30.000000
$animation a_runNE_RunIdle_KNIFE "a_runNE_RunIdle_KNIFE" loop fps 30.000000
$sequence r_RunIdle_KNIFE "a_runSW_RunIdle_KNIFE" loop ACT_DOD_RUN_AIM_KNIFE 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_KNIFE a_runW_RunIdle_KNIFE a_runNW_RunIdle_KNIFE a_runS_RunIdle_KNIFE a_runI_RunIdle_KNIFE a_runN_RunIdle_KNIFE a_runSE_RunIdle_KNIFE a_runE_RunIdle_KNIFE a_runNE_RunIdle_KNIFE
}
$sequence blend_sprintN_SprintAim_KNIFE "blend_sprintN_SprintAim_KNIFE" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintAim_KNIFE "a_sprintI_SprintAim_KNIFE" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintAim_KNIFE "a_runSW" loop ACT_DOD_SPRINT_AIM_KNIFE 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintAim_KNIFE a_sprintN a_runSW a_runE a_sprintNE
}
$sequence Attack_KNIFE "Attack_KNIFE" ACT_DOD_PRIMARYATTACK_KNIFE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackCrouch_KNIFE "AttackCrouch_KNIFE" ACT_DOD_PRIMARYATTACK_CROUCH_KNIFE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackProne_KNIFE "AttackProne_KNIFE" ACT_DOD_PRIMARYATTACK_PRONE_KNIFE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence StandIdle_SPADE "StandIdle_SPADE" loop ACT_DOD_STAND_AIM_SPADE 1 fps 30.00
$sequence CrouchIdle_SPADE "CrouchIdle_SPADE" loop ACT_DOD_CROUCH_AIM_SPADE 1 fps 30.00
$sequence ProneAim_SPADE "ProneAim_SPADE" loop ACT_DOD_PRONE_AIM_SPADE 1 fps 30.00
$sequence ProneWalkAim_SPADE "ProneWalkAim_SPADE" loop ACT_DOD_PRONEWALK_AIM_SPADE 1 fps 30.00
$sequence pose_blend_walkN_WalkIdle_SPADE "pose_blend_walkN_WalkIdle_SPADE" fps 30.00
$animation a_walkSW "a_walkSW" loop fps 35.000000
$animation a_walkW "a_walkW" loop fps 35.000000
$animation a_walkNW "a_walkNW" loop fps 35.000000
$animation a_walkS "a_walkS" loop fps 35.000000
$animation a_pose_walkI_WalkIdle_SPADE "a_pose_walkI_WalkIdle_SPADE" loop fps 30.000000
$animation a_walkN "a_walkN" loop fps 35.000000
$animation a_walkSE "a_walkSE" loop fps 35.000000
$animation a_walkE "a_walkE" loop fps 35.000000
$animation a_walkNE "a_walkNE" loop fps 35.000000
$sequence w_WalkIdle_SPADE "a_walkSW" loop ACT_DOD_WALK_AIM_SPADE 1 fps 35.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_walkSW a_walkW a_walkNW a_walkS a_pose_walkI_WalkIdle_SPADE a_walkN a_walkSE a_walkE a_walkNE
}
$sequence blend_crouchN_CrouchWalkIdle_SPADE "blend_crouchN_CrouchWalkIdle_SPADE" loop fps 30.00
$animation a_crouchSW "a_crouchSW" loop fps 30.000000
$animation a_crouchW "a_crouchW" loop fps 30.000000
$animation a_crouchNW "a_crouchNW" loop fps 30.000000
$animation a_crouchS "a_crouchS" loop fps 30.000000
$animation a_crouchI_CrouchWalkIdle_SPADE "a_crouchI_CrouchWalkIdle_SPADE" loop fps 30.000000
$animation a_crouchN "a_crouchN" loop fps 30.000000
$animation a_crouchSE "a_crouchSE" loop fps 30.000000
$animation a_crouchE "a_crouchE" loop fps 30.000000
$animation a_crouchNE "a_crouchNE" loop fps 30.000000
$sequence c_CrouchWalkIdle_SPADE "a_crouchSW" loop ACT_DOD_CROUCHWALK_AIM_SPADE 1 fps 30.00 {
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_crouchSW a_crouchW a_crouchNW a_crouchS a_crouchI_CrouchWalkIdle_SPADE a_crouchN a_crouchSE a_crouchE a_crouchNE
}
$animation a_runSW_RunIdle_SPADE "a_runSW_RunIdle_SPADE" loop fps 30.000000
$animation a_runW_RunIdle_SPADE "a_runW_RunIdle_SPADE" loop fps 30.000000
$animation a_runNW_RunIdle_SPADE "a_runNW_RunIdle_SPADE" loop fps 30.000000
$animation a_runS_RunIdle_SPADE "a_runS_RunIdle_SPADE" loop fps 30.000000
$animation a_runI_RunIdle_SPADE "a_runI_RunIdle_SPADE" loop fps 30.000000
$animation a_runN_RunIdle_SPADE "a_runN_RunIdle_SPADE" loop fps 30.000000
$animation a_runSE_RunIdle_SPADE "a_runSE_RunIdle_SPADE" loop fps 30.000000
$animation a_runE_RunIdle_SPADE "a_runE_RunIdle_SPADE" loop fps 30.000000
$animation a_runNE_RunIdle_SPADE "a_runNE_RunIdle_SPADE" loop fps 30.000000
$sequence r_RunIdle_SPADE "a_runSW_RunIdle_SPADE" loop ACT_DOD_RUN_AIM_SPADE 1 fps 30.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW_RunIdle_SPADE a_runW_RunIdle_SPADE a_runNW_RunIdle_SPADE a_runS_RunIdle_SPADE a_runI_RunIdle_SPADE a_runN_RunIdle_SPADE a_runSE_RunIdle_SPADE a_runE_RunIdle_SPADE a_runNE_RunIdle_SPADE
}
$sequence blend_sprintN_SprintAim_SPADE "blend_sprintN_SprintAim_SPADE" loop fps 30.00
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runW "a_runW" loop fps 33.000000
$animation a_sprintNW "a_sprintNW" loop fps 30.000000
$animation a_runS "a_runS" loop fps 33.000000
$animation a_sprintI_SprintAim_SPADE "a_sprintI_SprintAim_SPADE" loop fps 30.000000
$animation a_sprintN "a_sprintN" loop fps 30.000000
$animation a_runSW "a_runSW" loop fps 33.000000
$animation a_runE "a_runE" loop fps 33.000000
$animation a_sprintNE "a_sprintNE" loop fps 30.000000
$sequence s_SprintAim_SPADE "a_runSW" loop ACT_DOD_SPRINT_AIM_SPADE 1 fps 33.00 {
  { event 7001 14 "lfoot" }
  { event 7001 5 "rfoot" }
  blendwidth 9
  blend move_y -1.000000 1.000000
  blend move_y -1.000000 1.000000
 a_runSW a_runW a_sprintNW a_runS a_sprintI_SprintAim_SPADE a_sprintN a_runSW a_runE a_sprintNE
}
$sequence Attack_SPADE "Attack_SPADE" ACT_DOD_PRIMARYATTACK_SPADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackCrouch_SPADE "AttackCrouch_SPADE" ACT_DOD_PRIMARYATTACK_CROUCH_SPADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$sequence AttackProne_SPADE "AttackProne_SPADE" ACT_DOD_PRIMARYATTACK_PRONE_SPADE 1 fps 30.00 subtract mdldecompiler_delta.smd 0 {
  { event 7002 24 "2" }
}

$ikchain rhand ValveBiped.Bip01_R_Hand knee  0.707 0.707 0.000
$ikchain lhand ValveBiped.Bip01_L_Hand knee  0.707 0.707 0.000
$ikchain rfoot ValveBiped.Bip01_R_Foot knee  0.707 -0.707 0.000
$ikchain lfoot ValveBiped.Bip01_L_Foot knee  0.707 -0.707 0.000
