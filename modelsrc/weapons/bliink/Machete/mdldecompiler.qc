$cd "C:\Users\James\Documents"
$modelname "weapons/W_crowbar.mdl"
$model "studio" "w_Crowbar_reference.smd"

$lod 15
 {
  replacemodel "w_Crowbar_reference" "lod1_w_Crowbar_reference"
}
$cdmaterials "models\weapons\v_Crowbar\"
$hboxset "default"
$hbox 0 "ValveBiped.Bip01_R_Hand" 0.000  -3.636  -25.478  7.125  0.000  8.861
$surfaceprop "crowbar"
$illumposition -1.456 -0.510 0.723
$sequence idle "idle" loop ACT_VM_IDLE 1 fps 30.00
$sequence attack1 "attack1" fps 30.00
