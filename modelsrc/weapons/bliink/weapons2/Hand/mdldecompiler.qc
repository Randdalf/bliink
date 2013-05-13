
$modelname "Weapons/v_bliink_machete.mdl"
$model "default" "crowbar_reference.001.smd"
$scale 1.0
$origin 150 200 20

$cdmaterials "models\Weapons\V_hand\"
$cdmaterials "models\Weapons\bliink_machete\"
$hboxset "default"
$hbox 0 "ValveBiped.HandControlRotR" 0.000  -1.935  -15.150  11.123  0.000  0.000
$attachment "0" "ValveBiped.Tip" 0.00 -0.00 -0.00 rotate -0.00 -0.00 0.00
$surfaceprop "default"
$illumposition 25.370 -8.644 -15.379
$sequence idle01 "idle01" loop ACT_VM_IDLE 1 fps 30.00
$sequence draw "draw" ACT_VM_DRAW 1 fps 30.00
$sequence misscenter1 "misscenter1" ACT_VM_MISSCENTER 1 fps 30.00 rotate 45
$sequence misscenter2 "misscenter2" ACT_VM_MISSCENTER 1 fps 30.00 rotate 45
$sequence hitcenter1 "hitcenter1" ACT_VM_HITCENTER 1 fps 30.00 rotate 45
$sequence hitcenter2 "hitcenter2" ACT_VM_HITCENTER 1 fps 30.00 rotate 45
$sequence hitcenter3 "hitcenter3" ACT_VM_HITCENTER 1 fps 30.00 rotate 45
$sequence hitkill1 "hitkill1" ACT_VM_HITKILL 1 fps 30.00 rotate 90
$sequence holster "holster" ACT_VM_HOLSTER 1 fps 30.00 rotate 90
