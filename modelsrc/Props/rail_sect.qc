$modelname	"props\rail_sect.mdl"
$cdmaterials	"models\props\"
$scale 20

$body mybody	"rail_sect.smd"
$staticprop
$surfaceprop	combine_metal


$sequence idle	"rail_sect.smd"

$collisionmodel	"rail_sect.smd" { $concave }