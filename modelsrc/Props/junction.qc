$modelname	"props\junction.mdl"
$cdmaterials	"models\props\"
$scale 60

$body mybody	"junction.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"junction.smd"

$collisionmodel	"junction.smd" { $concave }