$modelname	"props\chair.mdl"
$cdmaterials	"models\props\"
$scale 50

$body mybody	"chair.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"chair.smd"

$collisionmodel	"chair.smd" { $concave }