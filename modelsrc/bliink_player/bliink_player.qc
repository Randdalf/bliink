$includemodel "player/sdk_player_shared.mdl"

$cd "C:\Program Files (x86)\Steam\steamapps\sourcemods\projectbliink\modelsrc\bliink_player\"
$modelname "player\bliink_player.mdl"

$model "body" "blue_player_reference.smd"

$poseparameter body_pitch -45.00 45.00
$poseparameter body_yaw -45.00 45.00
$poseparameter body_height 28.00 58.00
$cdmaterials "models\player\bliink\"$cd "C:\Program Files (x86)\Steam\steamapps\sourcemods\projectbliink\modelsrc\player\"

$hboxset "sdk"
$hbox 2 "ValveBiped.Bip01_Pelvis" -7.750  -3.000  -6.600  7.750  3.000  4.900
$hbox 6 "ValveBiped.Bip01_L_Thigh" 3.500  -3.900  -3.900  19.500  3.100  3.100
$hbox 6 "ValveBiped.Bip01_L_Calf" 1.520  -3.370  -3.250  16.510  3.630  3.250
$hbox 6 "ValveBiped.Bip01_L_Foot" -1.000  -1.300  -2.000  5.000  2.700  2.000
$hbox 6 "ValveBiped.Bip01_L_Toe0" -3.200  -1.450  -2.000  3.800  1.050  2.000
$hbox 7 "ValveBiped.Bip01_R_Thigh" 3.500  -3.900  -3.100  19.500  3.100  3.900
$hbox 7 "ValveBiped.Bip01_R_Calf" 1.520  -3.370  -3.250  16.510  3.630  3.250
$hbox 7 "ValveBiped.Bip01_R_Foot" -1.000  -1.300  -2.000  5.000  2.700  2.000
$hbox 7 "ValveBiped.Bip01_R_Toe0" -3.200  -1.450  -2.000  3.800  1.050  2.000
$hbox 2 "ValveBiped.Bip01_Spine" -0.450  -3.000  -7.000  4.050  7.000  7.000
$hbox 2 "ValveBiped.Bip01_Spine1" -0.900  -3.000  -7.000  4.100  8.000  7.000
$hbox 2 "ValveBiped.Bip01_Spine2" -0.500  -3.900  -7.500  7.500  7.100  7.500
$hbox 2 "ValveBiped.Bip01_Spine4" -0.200  -2.800  -7.500  3.800  5.200  7.500
$hbox 1 "ValveBiped.Bip01_Neck1" 0.500  -3.700  -2.500  3.500  1.300  2.500
$hbox 1 "ValveBiped.Bip01_Head1" -1.300  -5.150  -3.000  7.700  3.150  3.000
$hbox 4 "ValveBiped.Bip01_L_UpperArm" -3.000  -2.050  -2.450  13.000  2.450  2.050
$hbox 4 "ValveBiped.Bip01_L_Forearm" -0.400  -2.000  -2.800  11.200  2.200  1.800
$hbox 4 "ValveBiped.Bip01_L_Hand" 0.000  -1.650  -1.450  5.000  0.350  2.050
$hbox 5 "ValveBiped.Bip01_R_UpperArm" -3.000  -2.050  -2.050  13.000  2.450  2.450
$hbox 5 "ValveBiped.Bip01_R_Forearm" -0.400  -1.900  -1.800  11.200  2.100  2.400
$hbox 5 "ValveBiped.Bip01_R_Hand" 0.000  -1.650  -2.050  5.000  0.350  1.450
$hboxset "sdk_no_arms"
$hbox 2 "ValveBiped.Bip01_Pelvis" -7.750  -3.000  -6.600  7.750  3.000  4.900
$hbox 6 "ValveBiped.Bip01_L_Thigh" 3.500  -3.900  -3.900  19.500  3.100  3.100
$hbox 6 "ValveBiped.Bip01_L_Calf" 1.520  -3.370  -3.250  16.510  3.630  3.250
$hbox 6 "ValveBiped.Bip01_L_Foot" -1.000  -1.300  -2.000  5.000  2.700  2.000
$hbox 6 "ValveBiped.Bip01_L_Toe0" -3.200  -1.450  -2.000  3.800  1.050  2.000
$hbox 7 "ValveBiped.Bip01_R_Thigh" 3.500  -3.900  -3.100  19.500  3.100  3.900
$hbox 7 "ValveBiped.Bip01_R_Calf" 1.520  -3.370  -3.250  16.510  3.630  3.250
$hbox 7 "ValveBiped.Bip01_R_Foot" -1.000  -1.300  -2.000  5.000  2.700  2.000
$hbox 7 "ValveBiped.Bip01_R_Toe0" -3.200  -1.450  -2.000  3.800  1.050  2.000
$hbox 2 "ValveBiped.Bip01_Spine" -0.450  -3.000  -7.000  4.050  7.000  7.000
$hbox 2 "ValveBiped.Bip01_Spine1" -0.900  -3.000  -7.000  4.100  8.000  7.000
$hbox 2 "ValveBiped.Bip01_Spine2" -0.500  -3.900  -7.500  7.500  7.100  7.500
$hbox 2 "ValveBiped.Bip01_Spine4" -0.200  -2.800  -7.500  3.800  5.200  7.500
$hbox 1 "ValveBiped.Bip01_Neck1" 0.500  -3.700  -2.500  3.500  1.300  2.500
$hbox 1 "ValveBiped.Bip01_Head1" -1.300  -5.150  -3.000  7.700  3.150  3.000
$attachment "weapon_bone" "ValveBiped.weapon_bone" 0.00 0.00 -0.00 rotate -0.00 -0.00 -0.00
$attachment "weapon_bone_left" "ValveBiped.weapon_bone_left" 0.00 0.00 0.00 rotate 0.00 0.00 -0.00
$attachment "2" "ValveBiped.Bip01_Head1" -0.00 0.00 0.00 rotate -0.00 0.00 0.00
$attachment "head" "ValveBiped.Bip01_Head1" -0.00 0.00 0.00 rotate -0.00 0.00 0.00
$includemodel "player/sdk_player_shared.mdl"
$surfaceprop "flesh"
$illumposition -2.946 -0.318 36.149
$sequence ragdoll "ragdoll" ACT_DIERAGDOLL 1 fps 30.00
$ikchain rhand ValveBiped.Bip01_R_Hand knee  0.707 0.707 0.000
$ikchain lhand ValveBiped.Bip01_L_Hand knee  0.707 0.707 0.000
$ikchain rfoot ValveBiped.Bip01_R_Foot knee  0.707 -0.707 0.000
$ikchain lfoot ValveBiped.Bip01_L_Foot knee  0.707 -0.707 0.000
$bonemerge "ValveBiped.Bip01_R_Toe0"
$bonemerge "ValveBiped.Bip01_L_Toe0"