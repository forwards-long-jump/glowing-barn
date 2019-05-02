function getRequiredComponents()
  return {"position", "size", "player", "shooter"}
end

local scaling = 1
function update()
  -- Change scene when splace is pressed
  if(game.input:isKeyDown(32)) then
    game.core:setScene("game")
  end

  for i, entity in ipairs(entities) do

    -- Move player
    if(game.input:isKeyDown(40)) then
      entity.position.y = entity.position.y + 5
    end
    if(game.input:isKeyDown(38)) then
      entity.position.y = entity.position.y - 5
    end
    if(game.input:isKeyDown(39)) then
      entity.position.x = entity.position.x + 5
    end
    if(game.input:isKeyDown(37)) then
      entity.position.x = entity.position.x - 5
    end

    if(game.input:isKeyDown(48)) then
      game.camera:clearBoundary()
    end

     if(game.input:isKeyDown(57)) then
      game.camera:setBoundary(0, 0, game.core:getGameWidth(), game.core:getGameHeight())
    end

    if(game.input:isKeyDown(107)) then
      scaling = scaling * 1.1
      game.camera:setTargetScaling(scaling)
    end
    if(game.input:isKeyDown(109)) then
      scaling = scaling / 1.1
      game.camera:setTargetScaling(scaling)
    end

    -- Force to stay in map
    if entity.position.y < 0 then
      entity.position.y = 0
    end

    if entity.position.x < 0 then
      entity.position.x = 0
    end

    if entity.position.x + entity.size.width > 1280 then
      entity.position.x = 1280 - entity.size.width
    end

    if entity.position.y + entity.size.height > 720 then
      entity.position.y = 720 - entity.size.height
    end

    game.camera:centerTargetAt(entity.position.x, entity.position.y, entity.size.width, entity.size.height)

    -- f = shooting
    if(game.input:isKeyDown(70)) then
      if entity.shooter.currentShootingDelay < 0 then
        bullet = game.core:createEntity("bullet")
        bullet.position.x = entity.position.x + entity.size.width
        bullet.position.y = entity.position.y + 5
        bullet.speed.dx = entity.shooter.speedX
        entity.shooter.currentShootingDelay = entity.shooter.shootingDelay
      end
    end
    entity.shooter.currentShootingDelay = entity.shooter.currentShootingDelay - 1
  end
end
