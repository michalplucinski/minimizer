    SELECT  first_atomic_number
           ,first_atom.ionic_radius AS first_ionic_radius
           ,second_atomic_number
           ,second_atom.ionic_radius AS second_ionic_radius
           ,dissociation_energy
      FROM atom first_atom
INNER JOIN bond
        ON first_atom.atomic_number = bond.first_atomic_number
INNER JOIN atom second_atom
        ON bond.second_atomic_number = second_atom.atomic_number
           ;