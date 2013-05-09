$modelname	"weapons\w_bliink_machete.mdl"
$cdmaterials	"models\weapons\w_models\w_bliink_machete\"
$scale 0.50

$body mybody	"w_bliink_machete.smd"
$staticprop
$surfaceprop	combine_metal

$sequence idle	"idle.smd" fps 30 ACT_IDLE 1

$collisionmodel	"w_bliink_machete.smd" { $concave }