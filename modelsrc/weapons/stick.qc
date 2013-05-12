$modelname	"weapons\w_bliink_stick.mdl"
$cdmaterials	"models\weapons\w_models\w_bliink_stick\"
$scale 1.0
$origin 0 10 -60

$body mybody	"Stick.smd"
$staticprop
$surfaceprop	combine_metal

$sequence idle	"stick.smd" fps 30 ACT_IDLE 1

$collisionmodel	"stick.smd" { $concave }