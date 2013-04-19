CREATE TABLE atom(
   atomic_number INTEGER
  ,ionic_radius  REAL
  ,PRIMARY KEY(id)
);

CREATE TABLE bond(
   first_atomic_number  INTEGER
  ,second_atomic_number INTEGER
  ,dissociation_energy  REAL
  ,PRIMARY KEY(first_atom_id, second_atom_id)
);