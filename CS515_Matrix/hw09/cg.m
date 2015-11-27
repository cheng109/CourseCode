function [x, res] = cg(A, b, max_it, tol)

%  -- Iterative template routine --
%     Univ. of Tennessee and Oak Ridge National Laboratory
%     October 1, 1993
%     Details of this algorithm are described in "Templates for the
%     Solution of Linear Systems: Building Blocks for Iterative
%     Methods", Barrett, Berry, Chan, Demmel, Donato, Dongarra,
%     Eijkhout, Pozo, Romine, and van der Vorst, SIAM Publications,
%     1993. (ftp netlib2.cs.utk.edu; cd linalg; get templates.ps).
%
%  [x, res] = cg(A, b, max_it, tol)
%
% cg.m solves the symmetric positive definite linear system Ax=b 
% using the Conjugate Gradient method with preconditioning.
%
% input   A        REAL symmetric positive definite matrix
%         b        REAL right hand side vector
%         max_it   INTEGER maximum number of iterations
%         tol      REAL error tolerance
%
% output  x        REAL solution vector
%         error    REAL residual norms from each iteration

% Modfied for CS515 by David F. Gleich

  bnrm2 = norm( b );
  if  ( bnrm2 == 0.0 ), bnrm2 = 1.0; end
  if ~exist('tol','var') || isempty(tol), tol = 1e-8; end

  x = b; x(:) = 0;
  r = b;
  error = norm( r ) / bnrm2;
  if ( error < tol ) return, end
  res = zeros(max_it,1);

  for iter = 1:max_it                       % begin iteration

     z  = r;
     rho = (r'*z);

     if ( iter > 1 ),                       % direction vector
        beta = rho / rho_1;
        p = z + beta*p;
     else
        p = z;
     end

     q = A*p;
     alpha = rho / (p'*q );
     x = x + alpha * p;                    % update approximation vector

     r = r - alpha*q;                      % compute residual
     res(iter) = norm( r ) / bnrm2;            % check convergence
     if ( res(iter) <= tol ), break, end 

     rho_1 = rho;

  end
  res = res(1:iter);
% END cg.m