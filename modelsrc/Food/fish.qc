$modelname	"props\fish.mdl"
$cdmaterials	"models\props\"
$scale 2

$body mybody	"fish.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"fish.smd"

$collisionmodel	"fish.smd" { $concave }