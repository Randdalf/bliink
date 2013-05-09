$modelname	"weapons\w_bliink_bat.mdl"
$cdmaterials	"models\weapons\w_models\w_bliink_bat\"
$scale 4.0
$origin 0 10 -60

$body mybody	"bat.smd"
$staticprop
$surfaceprop	combine_metal

$sequence idle	"bat.smd" fps 30 ACT_IDLE 1

$collisionmodel	"bat.smd" { $concave }