$modelname	"props\sandwich.mdl"
$cdmaterials	"models\props\"
$scale 100

$body mybody	"sandwich.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"sandwich.smd"

$collisionmodel	"sandwich.smd" { $concave }