$modelname	"props\rail.mdl"
$cdmaterials	"models\props\"
$scale 20

$body mybody	"rail.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"rail.smd"

$collisionmodel	"rail.smd" { $concave }