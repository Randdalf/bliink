$modelname	"weapons\w_bliink_pistol.mdl"
$cdmaterials	"models\weapons\w_models\w_bliink_pistol\"
$scale 1.00

$body mybody	"pistol.smd"
$staticprop
$surfaceprop	combine_metal

$sequence idle	"w_pist_deagle.smd" fps 30 ACT_IDLE 1

$collisionmodel	"w_pist_deagle.smd" { $concave }